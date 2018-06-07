#include<reg51.h>
#include <intrins.h>
#include <absacc.h>
unsigned char BUFF[5]={1,1,1,1,1},KEY_DATA,s;
void dmsec (unsigned int count) { // mSec Delay
 unsigned int i; // Keil CA51 (x2)
 while (count)
{ i = 230; while (i>0) i--;
 count--; }
}
void changBUFF(unsigned	char level)
{
	unsigned int i;
	for(i=0;i<4;i++)
	{
		BUFF[i]=BUFF[i+1];
	}
	BUFF[4]= level;
}
unsigned char startlevel()
{
	unsigned char le[3]={0,0,0},i,max,c;
	for(i=0;i<5;i++)
	{
		if(BUFF[i]==1)
		{
			le[0]++;
		}
		else if(BUFF[i]==2)
		{
			le[1]++;
		}
		else if(BUFF[i]==3)
		{
			le[2]++;
		}
	}
	max=le[0];
	c=0;
	for(i=1;i<3;i++)
	{
		if(le[i]>max)
		{
			max=le[i];
			c=i;
		}
		else if(le[i]==max)
		{
			max=le[c+1];
			c++;
		}
	}
	return (c+1);
} 
unsigned char get_key (void) {// get key
unsigned char i,j,x,colx,w,rowx,k;
colx=0xfe;//11111110
rowx=0xf7;//11110111
P3=0x78; //01111000
k=0xff;
x = P3; // check for key press
if (x!=0x78)
{
dmsec(30);
if (x!=0x78)
// new press accepted
{ for (i=0;i<=2;i++)
// look for col
{ P3=colx;
w=P3&0x78;
colx=_crol_(colx,1);
if(w!=0x78)
{
for (j=0;j<=3;j++)
{
if (w==(rowx&0x78)){k=i+3*j+1;}
rowx=_crol_(rowx,1);
}
}
}
}
}
return (k);
}
void main (void)
{
P1 = 0xff;
P3 = 0xff;
while (1)
 {
 	KEY_DATA = get_key();
	if (KEY_DATA== 12){
		s=startlevel();
		if (s== 1){
			P1=0xfe;
		}
		else if (s== 2){
			P1=0xfd;
		}
		else if (s== 3){
			P1=0xfb;
		}
		while(KEY_DATA!=11)
		{
			KEY_DATA = get_key();
			if (KEY_DATA== 1){
				P1=0xfe;
				changBUFF(1);
				while(KEY_DATA!=0xff)
				{
					KEY_DATA = get_key();
					dmsec(30);
				}
			}
			else if (KEY_DATA== 2){
				P1=0xfd;
				changBUFF(2);
				while(KEY_DATA!=0xff)
				{
					KEY_DATA = get_key();
					dmsec(30);
				}
			}
			else if (KEY_DATA== 3){
				P1=0xfb;
				changBUFF(3);
				while(KEY_DATA!=0xff)
				{
					KEY_DATA = get_key();
					dmsec(30);
				}
			}
		}
		P1=0xff;
 	}
 }//End of while
}//End of program