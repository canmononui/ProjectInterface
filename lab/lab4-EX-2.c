/*File : LAB4_3.c 
Description : Stepping motor, 1-phase drive 
Clock : 29.4912 MHz 
Hardware: Stepping motor module, Step  angle 18 
Compiler: Keil C Compiler 
*/ 
/*Connect INA to Port1.0, INB to Port1.1,INC to Port1.2 and IND to Port1.3*/  
/* 1 phase drive*/ 
/*Step angle 18*/ 
#include<reg52.h> 
int step; 
/********** DELAY FUNCTION **********/ 
void delay1 (unsigned int count) //  Delay 
{     unsigned int i;            // Keil CA51 (x2)  
    while (count) { 
        i = 100; while (i>0) i--; 
        count--;    } 
} 

/********** MAIN PROGRAM **********/ 
void main() 
{  
 	step = 0x11; 
 	while(1) 
 	{ 	for(int i = 0;i<10;i++)
		{
   			P1=step; 
   			step = _crol_(step,1); 
   			delay1(400);
		}

		for(int j = 0;j<10;j++)
		{
   			P1=step; 
   			step = _crol_(step,25); 
   			delay1(400);
		}

		for(int k = 0;k<10;k++)
		{
   			P1=step; 
   			step = _crol_(step,50); 
   			delay1(400);
		}
 	} 
}// end of main()
