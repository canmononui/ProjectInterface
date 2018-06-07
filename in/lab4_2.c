#include<reg52.h>
int step;
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
while(1)
{
step = 0x33;
P1=step;
step = _crol_(step,1);
delay1(200);

P1=step;
step = _crol_(step,1);
delay1(200);

P1=step;
step = _crol_(step,1);
delay1(200);

P1=step;
step = _crol_(step,1);
delay1(200);

P1=step;
step = _crol_(step,1);
delay1(400);

P1=step;
step = _crol_(step,1);
delay1(400);

P1=step;
step = _crol_(step,1);
delay1(400);

P1=step;
step = _crol_(step,1);
delay1(400);

P1=step;
step = _crol_(step,1);
delay1(600);

P1=step;
step = _crol_(step,1);
delay1(600);

P1=step;
step = _crol_(step,1);
delay1(600);

P1=step;
step = _crol_(step,1);
delay1(600);

step=0x80;
P1=step;
delay1(200);

step=0xc0;
P1=step;
delay1(200);

step=0x40;
P1=step;
delay1(200);

step=0x60;
P1=step;
delay1(200);

step=0x80;
P1=step;
delay1(400);

step=0xc0;
P1=step;
delay1(400);

step=0x40;
P1=step;
delay1(400);

step=0x60;
P1=step;
delay1(400);

step=0x80;
P1=step;
delay1(600);

step=0xc0;
P1=step;
delay1(600);

step=0x40;
P1=step;
delay1(600);

step=0x60;
P1=step;
delay1(600);
}
}// end of main()