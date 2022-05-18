unsigned long ncols = 0;
unsigned long nrows = 0; 
int column_scan_index;
int row_scan_index;
void delayms(unsigned long time);
unsigned char sw1 ();
unsigned char sw2 ();
#include "stdbool.h"
bool switch_2 = false;
bool switch_1 = false;

/* Array of 4x4 to define characters which will be printe on specific key pressed */
unsigned const char symbol[4][4] = {{ '1', '2',  '3', 'A'},      
																		{  '4', '5',  '6', 'B'},      
																		{  '7', '8',  '9', 'C'},      
																		{  '*', '0',  '#', 'D'}};

/* Keypad_Init() configures PORTC and PORTE to scan keypad keys */

void keypad_Init()
{
 	SYSCTL_RCGCGPIO_R |= 0x14;            //enable clc for port C & E  
  	while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be enabled
 	GPIO_PORTC_CR_R  |= 0xF0;             //allow changes to all the bits in port C
  GPIO_PORTE_CR_R  |= 0x1E;             //allow changes to all the bits in port E
  GPIO_PORTC_DIR_R |= 0xF0;             //set directions cols are o/ps
	GPIO_PORTE_DIR_R &=~ 0x1E;             //set directions raws are column_scan_index/ps
	GPIO_PORTE_PDR_R |= 0x1E;             //pull down resistor on Raws
	GPIO_PORTC_DEN_R |= 0xF0;             //digital enable pins in port C
	GPIO_PORTE_DEN_R |= 0x1E;             //digital enable pins in port E
}

/* keypad_getkey() function returns the value of key pressed by the user by traversing columns
and rows respectivley */
char keypad_input()	
{
 	while(1)		
	{
					// SW 2 is pressed
					if (sw2 () == 0) 
						{
							switch_2 = true;
							break;						
						}
					// SW 1 is pressed
					if (sw1 () == 0) 
						{
							switch_1 = true;
							break;	
						}
		for(column_scan_index = 0; column_scan_index < 4; column_scan_index++)		//scan columns
		{
			GPIO_PORTC_DATA_R = (1 << (column_scan_index+4) );
			delayms (1);
			
			for(row_scan_index = 0; row_scan_index < 4; row_scan_index++)	//scan rows
				{

					
					if( (GPIO_PORTE_DATA_R & 0x1E) & (1 << (row_scan_index+1) ) )
					return symbol[row_scan_index][column_scan_index];   //return data of pressed button
				}
		}
	}
}
