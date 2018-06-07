#include <reg52.h>
#include <stdio.h>    
#include <intrins.h>
#include <absacc.h>

/* AT89C51ED2 SFR */
sfr CKCON = 0x8F;    
  // Clock Control

/* LCD Interface */
#define PORT_LCD  P0        // LCD Interface = Port P0
sbit RS = PORT_LCD^3;    // RS LCD (0=Instruction,1=Data) 
sbit RW = PORT_LCD^2;   // RW LCD (0=Write,1=Read) 
sbit E  = PORT_LCD^1;   // Enable LCD(Active = "1") 
char lcdbuf[16+1];    // LCD Display Buffer
unsigned char KEY_DATA,n;

/* prototype  section */
void init_lcd(void);    // Initial Character LCD(4-Bit Interface)
void gotolcd(unsigned char);   // Set Cursor LCD
void write_ins(unsigned char);       // Write Instruction LCD
void write_data(unsigned char);   // Write Data LCD
void enable_lcd(void);     // Enable Pulse
char busy_lcd(void);    // Read Busy LCD Status
void printlcd(void);    // Display Message LCD
void delay(unsigned long);   // Delay Time Function(1..4294967295)
void dmsec(unsigned int count2)
{
	TMOD = (TMOD & 0xF0) | 0x01;/* Set T/C0 Mode*/
	TR0=1;
	while (count2)
	{
		if (TF0==1)
		{
			TR0=0; /* Stop Timer 0*/
			TF0=0;
			count2--;
			TH0 = 0xEC; /* Load Timer withFFFFH- 5000 */
			TL0 = 0x77;
			TR0 = 1; /* Start Timer 0*/
		}
	}
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
		{ 
			for (i=0;i<=2;i++)
		// look for col
			{ 
				P3=colx; 
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

/*--------------------------------------------
The main C function.  Program execution Here 
---------------------------------------------*/
void main(void)
{
  	CKCON = 0x01;     // Initial X2 Mode (BUS Clock =58.9824 MHz)  
  	init_lcd();    // Initial LCD 
  	dmsec(100);

  	while(1)
  	{	
	  	gotolcd(0);
	  	KEY_DATA = get_key();
		if (KEY_DATA!= 0xff){
			if(KEY_DATA==1)
			{
				sprintf(lcdbuf,"1");
				printlcd();
			}
			if(KEY_DATA==2)
			{
				sprintf(lcdbuf,"2");
				printlcd();
			}
			if(KEY_DATA==3)
			{
				sprintf(lcdbuf,"3");
				printlcd();
			}
			if(KEY_DATA==4)
			{
				sprintf(lcdbuf,"4");
				printlcd();
			}
			if(KEY_DATA==5)
			{
				sprintf(lcdbuf,"5");
				printlcd();
			}
			if(KEY_DATA==6)
			{
				sprintf(lcdbuf,"6");
				printlcd();
			}
			if(KEY_DATA==7)
			{
				sprintf(lcdbuf,"7");
				printlcd();
			}
			if(KEY_DATA==8)
			{
				sprintf(lcdbuf,"8");
				printlcd();
			}
			if(KEY_DATA==9)
			{
				sprintf(lcdbuf,"9");
				printlcd();
			}
			if(KEY_DATA==10)
			{
				sprintf(lcdbuf,"*");
				printlcd();
			}
			if(KEY_DATA==11)
			{
				sprintf(lcdbuf,"0");
				printlcd();
			}
			if(KEY_DATA==12)
			{
				sprintf(lcdbuf,"#");
				printlcd();
			}
		}
  	} 
}

/*******************************/
/* Initial LCD 4-Bit Interface */
/*******************************/
void init_lcd(void)
{
	unsigned int i;     // Delay Count
	
	E = 0;      // Start LCD Control (Disable)
	RS = 0;      // Default Instruction 
	RW = 0;    // Default = Write Direction 
	for (i=0;i<10000;i++);    //Power-On Delay (15 mS)   
	     
	PORT_LCD &= 0x0F;          // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= 0x30;    // DB5:DB4 = 1:1
	enable_lcd();     // Enable Pulse
	for (i=0;i<2500;i++);    // Delay 4.1mS
	
	PORT_LCD &= 0x0F;          // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= 0x30;    // DB5:DB4 = 1:1
	enable_lcd();     // Enable Pulse
	for (i=0;i<100;i++);    // delay 100uS
	
	PORT_LCD &= 0x0F;          // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= 0x30;    // DB5:DB4 = 1:1 
	 
	enable_lcd();    // Enable Pulse 
	while(busy_lcd());          //Wait LCD Execute Complete 
	
	PORT_LCD &= 0x0F;          // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= 0x20;    // DB5:DB4 = 1:0
	enable_lcd();     // Enable Pulse
	while(busy_lcd());          // Wait LCD Execute Complete
	  
	write_ins(0x28);      // Function Set (DL=0: 4-Bit, N=1: 2 Line, F=0:5X7) 
	write_ins(0x0C);     // Display on/off Control (D=1 Display ON, C=1 Cursor OFF, B=0 Blink OFF) 
	write_ins(0x06);     // Entry Mode Set (M=1 Increment, S=0 Cursor Shift) 
	write_ins(0x01);     // Clear Display  (Clear Display, Set DD RAM Address=0) 
}
/******************/
/* Set LCD Cursor */
/******************/
void gotolcd(unsigned char i)
{
	i |= 0x80;     // Set DD-RAM Address Command
	write_ins(i);  
}

/****************************/
/* Write Instruction to LCD */
/****************************/
void write_ins(unsigned char i)
{
	RS  = 0;      // Instruction Select
	RW  = 0;     // Write Select
	
	PORT_LCD &= 0x0F;          // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= i & 0xF0;      // Strobe High Nibble Command 
	 
	enable_lcd();    // Enable Pulse 
	       
	PORT_LCD &= 0x0F;           // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= (i << 4) & 0xF0;   // Strobe Low Nibble Command
	enable_lcd();     // Enable Pulse
	    
	while(busy_lcd());          // Wait LCD Execute Complete
}

/****************************/
/* Write Data(ASCII) to LCD */
/****************************/
void write_data(unsigned char i)
{
	RS  = 1;       
	   // Data Select
	RW  = 0;     // Write Select
	PORT_LCD &= 0x0F;       // Clear old LCD Data (Bit[7..4]) 
	PORT_LCD |= i & 0xF0;      //Strobe High Nibble Data 
	enable_lcd();    // Enable Pulse   
	       
	PORT_LCD &= 0x0F;        // Clear old LCD Data (Bit[7..4])
	PORT_LCD |= (i << 4) & 0xF0;    // Strobe Low Nibble Data
	enable_lcd();     // Enable Pulse
	 
	while(busy_lcd());          // Wait LCD Execute Complete
}

/***********************/
/* Enable Pulse to LCD */
/***********************/
void enable_lcd(void)     
 // Enable Pulse
{
  	unsigned int i;     // Delay Count  
 
  	E = 1;       // Enable ON 
  	for (i=0;i<500;i++);
  	E = 0;        // Enable OFF 
}

/******************/
/* Wait LCD Ready */
/******************/
char busy_lcd(void)
{
  	unsigned char busy_status;   // Busy Status Read

  	RS  = 0;      // Instruction Select
  	RW  = 1;      // Read Direction
  	E = 1;      // Start Read Busy
  	busy_status = PORT_LCD;   // Read LCD Data
 	if(busy_status & 0x80)       //Read & Check Busy Flag 
  	{
    	E = 0;            // Disable Read
 		RW = 0;     // Default = Write Direction
    	return 1;     // LCD Busy Status
  	}
  	else
  	{
    	E = 0;            // Disable Read
 		RW = 0;     // Default = Write Direction
    	return 0;     // LCD Ready Status
  	}
}


/****************************/
/* Print Data(ASCII) to LCD */
/****************************/ 

 
void printlcd(void)
{
	  char *p;
	 
	  p = lcdbuf;
	 
	  do       // Get ASCII & Write to LCDUntil null 
	  {
	    write_data(*p);     // Write ASCII to LCD
	    p++;      // Next ASCII
	  }
	  while(*p != '\0');     // End of ASCII (null)
	 
	  return;
}


