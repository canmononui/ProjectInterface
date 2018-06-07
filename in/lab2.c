#include<reg51.h>
#include<intrins.h>
#include<absacc.h>
#define SEGM P0// segment
#define DIGIT P1// Digit,BL,485con,sound,user-led 

sbit SOUND = P3^0;
sbit light = P3^1;
unsigned int count;
unsigned char DISBUF[4], KEY_DATA; // display buffer
unsigned char code SEGCODE[12]={0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x76,0x3F,0x63}; 

void ex0_isr (void) interrupt 0
{
	TF0=1;
	ET0=1;
	light=1;
}
void timer0_ISR (void) interrupt 1
{
	TR0 = 0; /* Stop Timer 0*/
	TH0 = 0xFB; 
	TL0 = 0x7F;
	TR0 = 1; /* Start Timer 0*/
	SOUND=!SOUND;
}// end Timer0 ISR 
void dmsec(unsigned int count2)
{
	TR1=1;
	while (count2)
	{ 
		if (TF1==1)
		{ 
			TR1=0; /* Stop Timer 0*/
			TF1=0;
			count2--;
			TH1 = 0xEC; /* Load Timer withFFFFH- 5000 */
			TL1 = 0x77;
			TR1 = 1; /* Start Timer 0*/
		}
	}
}
/*************************************/
unsigned char get_key (void) {// get key 
	unsigned char i,j,x,colx,w,rowx,k;
	colx=0xfb;//11111011
	rowx=0xf7;//11110111
	P2=0x78; //01111000
	k=0xff;
	x = P2; // check for key press 
	if (x!=0x78)
	{ 
		for (i=0;i<=2;i++)
		// look for col
		{ 
			P2=colx;
			w=P2&0x78;
			colx=_cror_(colx,1);
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
	return (k);
}

void main (void)
{ 
	unsigned int i,n; 
	count=0;
	light=0;
	TMOD = 0x11; /* Set T/C0 Mode */
	EA=1;
	EX0=1;
	INT1=1;
	while (1)
	{	
		if(light==1)
		{
			KEY_DATA = get_key();
			if (KEY_DATA== 12){
				if (DISBUF[3]==0x5B &&	DISBUF[2]==0x4F && DISBUF[1]==0x3F && DISBUF[0]==0x4F){
					TR0=0;
					ET0=0;
					light=0;
				}
				for (n=0;n<=3;n++){
						DISBUF[n]=0x00;
				}
			}	
			else if (KEY_DATA!= 0xff){
				for (n=3;n>=1;n--){
					DISBUF[n]=DISBUF[n-1];
				}
				DISBUF[0]=SEGCODE[KEY_DATA-1]; 
			}
			for (i=0;i<=3;i++) {
				// scan display
				DIGIT = i;
				SEGM = DISBUF[i]; // out segment
				dmsec(7);
			}
		}
	}//end while
}// end main