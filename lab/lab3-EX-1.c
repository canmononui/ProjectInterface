/*  Filename     lab03_2.C 
Description  Test serial interrupt 
Clock        11.0592 Mhz 
Compiler     Keil CA51 v2.20a 
*/ 
#include <reg51.h> 
#include <stdio.h> 
#include <absacc.h> 
#include <stdlib.h> 
#define  SEG7LED P0 
#define SEGCHNL P1  
void dusec (unsigned int count); 
void start232 (void); 
void startinterupt(void); 
void serial_ISR(void); 
void serial_ISR_Job(void);  
int i=0; 
char dataSEG[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d, 
       0x7d,0x07,0x7f,0x6f,0x40}; 

//--------------------------------------------------  
void main() 
{ 
 	start232(); 
 	startinterupt(); 
 	printf("Test Serial Interupt \n\r"); 
 	while(1) 
 	{ 
  		for(i=0;i<8;i++) 
  		{ 
   			SEG7LED = dataSEG[i]; 
   			SEGCHNL =  i; 
   			dusec(1); 
  		} 
 	}// end while(1) 
}// end void main
  
/********** FUNCTIONS **********/ 
void dusec (unsigned int count) {  // mSec Delay 
    unsigned int i;                // Keil CA51 (x2)  
    while (count) { 
        i = 10; while (i>0) i--; 
        count--; 
    } 
} 
void start232 (void)  
{      
     SCON = 0x52; // set RS232 parameter 
    TMOD |= 0x21; // Crystal = 11059200 
    TH1 = -6; PCON |= 0x80;     // speed x 2=19200 
 	// TH1 = -12; PCON |= 0x80; // speed x 2=9600 
    TR1 = 1; 
}
void startinterupt(void) 
{ 
	 EA = 1; 
	 ES = 1; 
}  
void serial_ISR(void) interrupt 4  
{  
 	if(RI) 
 	{  
  		ES = 0; 
  		serial_ISR_Job(); 
  		RI = 0; 
  		ES = 1;    
	} 
}
  
void serial_ISR_Job(void) 
{ 
	int i; 
 	char mm; 
 	for(i=0;i<8;i++) 
 	{ 
  		mm=SBUF; 
	  	SEG7LED = mm; 
	  	SEGCHNL = i; 
	  	dusec(5000); 
	} 
  	dusec(1000); 
}  