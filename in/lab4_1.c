#include<reg52.h>
sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit EN = P1^2;
/********** BASIC FUNCTION **********/
void delay1 (unsigned int count) // mSec Delay
{ unsigned int i; // Keil CA51 (x2)
while (count) {
i = 100; while (i>0) i--;
count--; }
}
/********** MAIN PROGRAM **********/
void main()
{
P1 = 0xff;
while(1)
{
EN = 1;
IN1 = 0;
IN2 = 0;
delay1(900);
IN2 = 1;
IN1 = 0;
delay1(100);

IN1 = 0;
IN2 = 0;
delay1(500);
IN2 = 1;
IN1 = 0;
delay1(500);

IN1 = 0;
IN2 = 0;
delay1(100);
IN2 = 1;
IN1 = 0;
delay1(900);

IN1 = 0;
IN2 = 0;
delay1(100);
IN2 = 0;
IN1 = 0;
delay1(900);

IN1 = 0;
IN2 = 0;
delay1(900);
IN2 = 0;
IN1 = 1;
delay1(100);

IN1 = 0;
IN2 = 0;
delay1(500);
IN2 = 0;
IN1 = 1;
delay1(500);

IN1 = 0;
IN2 = 0;
delay1(100);
IN2 = 0;
IN1 = 1;
delay1(900);

IN1 = 0;
IN2 = 0;
delay1(100);
IN2 = 0;
IN1 = 0;
delay1(900);
}
}// end of main()