
#include "Macros.h"

void SystemInit(){};	
	
	int main()
	{
		LCD_init();
		LEDSW_Init();
		sw3_buzzer_init();
		keypad_Init();		
		Interrupt_Init();		
		
		while(1)
		{
			idle: LCD_string("Enter choice:");
			switch (keypad_input())
			{
				case 'A' : 
				pushA();
				break;
				
				case 'B' : 
				pushB();
				break;
				
				case 'C' : 
				pushC();
				break;
				
				case 'D' :
				pushD();
				break;
				
				case '0' :
				quick_cooking();
				break;
				
				default: 
					clear_LCD;
					goto idle;
			}

			
		}
}
