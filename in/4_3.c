#include<reg51.h>
#include <absacc.h>
#include <stdio.h>
/********** 8255 I/O PORT **********/
sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN = P1^2;
void start232(void);
/********** DELAY FUNCTION **********/
void delay1 (unsigned int count) // Delay
{ unsigned int i; // Keil CA51 (x2)
while (count) {
i = 100; while (i>0) i--;
count--; }
}
/********** MAIN PROGRAM **********/
void main()
{
start232();
TR0=1;
while(1)
{
EN = 1;
IN1 = 0;
IN2 = 0;
delay1(50);
IN2 = 1;
IN1 = 0;
delay1(50);
printf("Left");
EN = 1;
IN1 = 0;
IN2 = 0;
delay1(50);
IN2 = 0;
IN1 = 1;
delay1(50);
printf("Right");
}
}// end of main()
//**************** Function
void start232(void)
{
// speed x 2
SCON = 0x52; // set RS232 parameter
TMOD = 0x25; // Timer0 as counter
// TH1 = -6; PCON |= 0x80; //19200
TH1 = -12; PCON |= 0x80;//9600
TR1 =1;
RI = 0;
}