#include <stdint.h>
#include "tm4c123gh6pm.h"
int counter;

////	main delay block	/////
void SysTick_wait(unsigned long delay)												
			{
				NVIC_ST_CTRL_R = 0x0;
				NVIC_ST_RELOAD_R = delay-1;
				NVIC_ST_CURRENT_R = 0x0;
				NVIC_ST_CTRL_R	|= 0x5;					
				while( (NVIC_ST_CTRL_R & 0x00010000) == 0) {}				//Checking for count bit
			}
////	delay 1 m Sec	/////		
int delayms(unsigned long time)
		{
		for (counter=0; counter<time ; counter++)
		{
			SysTick_wait(16000);																																										
		}
		}
		
int delays_display(unsigned long time)												
		{
		for (counter=0; counter<time ; counter++)			//for(counter=time;counter>0;counter--)
		{
			LCD_data (counter);
			delayms(1000);
			sw3();//cheak if sw3 is pressed(door is open)
			//sw1();cheak if sw1 is pressed
		}
		counter = 0;
		}
		
void SystemInit(void){};
void LCD_data(unsigned char data)
{
	//GPIO_PORTA_DATA_R &= ~0x40; 	// R/W will be connected to the GND externally
	GPIO_PORTA_DATA_R |= 0x20; 		// RS = 1
	delayms(2);
	GPIO_PORTA_DATA_R |= 0x80; 		// EN = 1
	GPIO_PORTB_DATA_R = data;
	delayms(2);
	GPIO_PORTA_DATA_R &= ~0x80; 	// EN = 0
	delayms(2);
}
void LCD_command(unsigned char command)
{
	GPIO_PORTA_DATA_R &= ~0x20; 	// RS = 0
	delayms(2);
	GPIO_PORTA_DATA_R |= 0x80; 		// EN = 1
	GPIO_PORTB_DATA_R = command;
	delayms(2);
	GPIO_PORTA_DATA_R &= ~0x80; 	// EN = 0
	delayms(2);
}
void LCD_init()
{
	SYSCTL_RCGCGPIO_R |= 0x03; // PortA (Pin 5:RS)(Pin 6:R/W)(Pin 7:EN) & PortB (Pin 0-7:D0-7)
	while((SYSCTL_PRGPIO_R&0x03) == 0){}
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R = 0xFF;
	GPIO_PORTB_AFSEL_R = 0;
	GPIO_PORTB_PCTL_R  = 0;
	GPIO_PORTB_AMSEL_R = 0;
	GPIO_PORTB_PUR_R = 0;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTA_LOCK_R = 0x4C4F434B;
	GPIO_PORTA_CR_R |= 0xE0;
	GPIO_PORTA_AFSEL_R &= ~0xE0;
	GPIO_PORTA_PCTL_R  &= ~0xE0;
	GPIO_PORTA_AMSEL_R &= ~0xE0;
	GPIO_PORTA_PUR_R &= ~0xE0;
	GPIO_PORTA_DIR_R |= 0xE0;
	GPIO_PORTA_DEN_R |= 0xE0;
	LCD_command(0x20); // Set 5x7 Font size
	LCD_command(0x38); // 8-bit data
	LCD_command(0x02); // Return Cursor Home
	LCD_command(0x01); // clear
	LCD_command(0x0F); // diplay on & cursor blinking
	//LCD_command(0x30); // wakeup
}

	void LEDSW_Init(void)
				{
						SYSCTL_RCGCGPIO_R	|= 0x20;							//PORT F Clock enable
					
						while ( (SYSCTL_PRGPIO_R&0x20) == 0) {}
						
						GPIO_PORTF_LOCK_R |= 0x4C4F434B;				//Unlock PORT F
						GPIO_PORTF_CR_R |= 0x1F;								//Allow changes to pins 0,1,2,3,4
						GPIO_PORTF_DIR_R |= 0x0E;								//SET pins 1,2,3 to be output
						GPIO_PORTF_DIR_R &= ~0x11;							//SET pins 0,4 to be input
						GPIO_PORTF_DEN_R |= 0x1F;								//SET pins 0,1,2,3,4 to be digital
						GPIO_PORTF_AMSEL_R &= ~0x1F;						//Disable Analog function
						GPIO_PORTF_AFSEL_R &= ~0x1F;						//No alternative function
						GPIO_PORTF_PCTL_R &= ~0xFFFFF;					//GPIO clear bit PCTL
						GPIO_PORTF_DATA_R &= ~0x0E;							//Initialize LEDs to be off
						GPIO_PORTF_PUR_R |= 0x11;								//SET pull-up resistance
				}

/* Array of 4x4 to define characters which will be printe on specific key pressed */

unsigned int ncols = 0;
unsigned int nrows = 0;                                                                    
unsigned const char symbol[4][4] = {{ '1', '2',  '3', 'A'},      
																	 {  '4', '5',  '6', 'B'},      
                                   {  '7', '8',  '9', 'C'},      
                                   {  '*', '0',  '#', 'D'}}; 

		
/* Keypad_Init() configures PORTC and PORTE to scan keypad keys */
void keypad_Init(void)
{
  SYSCTL_RCGCGPIO_R |= 0x14;            //enable clc for port C & E  
  while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be enabled
  GPIO_PORTC_CR_R  |= 0xF0;             //allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTC_DIR_R |= 0xF0;             //set directions cols are o/ps
  GPIO_PORTE_DIR_R |= 0x00;             //set directions raws are i/ps
  GPIO_PORTE_PDR_R |= 0x1E;             //pull down resistor on Raws
  GPIO_PORTC_DEN_R |= 0xF0;             //digital enable pins in port C
  GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins in port E
}




/* keypad_getkey() function returns the value of key pressed by the user by traversing columns
and rows respectivley */
char keypad_getkey(void)
{
  while(1)
  {
				for(int i = 0; i < 4; i++)                       						 //scan columns
					{
					GPIO_PORTC_DATA_R = (1 << (i+4));
					delayms (1);
											for(int j = 0; j < 4; j++)                     //scan rows
											{
											if((GPIO_PORTE_DATA_R & 0x1E) & (1 << (j+1)))
											return symbol[j][i];
											}
					}
  }
}				

unsigned char SW1_Input (void)
			{
				
						return GPIO_PORTF_DATA_R & 0x10;
				
			}
