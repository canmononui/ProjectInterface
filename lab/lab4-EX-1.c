/*  Filename     lab01_4.C 
    Description  Test Input by Logic switch 
    Clock        11.0592 Mhz 
    Compiler     Keil  uvision 3 
*/ 
#include<reg51.h> 
#include <intrins.h> 
#include <absacc.h> 
char portLED; 
char portLEDSTOP; 
char myloop; 
sbit sw0 = P3^5; 
sbit sw1 = P3^6; 
/********** BASIC FUNCTION **********/ 
void dmsec (unsigned int count) // mSec Delay 
{     unsigned int i;                // Keil CA51 (x2)  
       while (count)  
       {        i = 230; while (i>0) i--;        count--;         } 
}
 
/********** MAIN PROGRAM **********/ 
void main() 
{ 
	P1 = 0x00; 
	while(1) 
	{ 
	 	if(sw0 == 1) 
	  	{ 
	  		portLED = 0x01;
			P1 = portLED; 
			portLED = portLED+1; 
			dmsec(200); 
	  	}   
	  	else if(sw1 == 1) 
	  	{ 
	  		portLEDSTOP = 0x00;
			P1 = portLEDSTOP;  
			dmsec(200);
			
			if(sw1 == 1) 
	  		{ 
				P1 = portLED;  
				dmsec(200);
	  		}
	  	}     
 	} 
}  