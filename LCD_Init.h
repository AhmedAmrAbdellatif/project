////     (PA5 -> RS) & (PA7 -> EN) & (PB0-7 -> D0-7)     ////

////     LCD character print     ////
void LCD_data(unsigned char data)
{
	GPIO_PORTA_DATA_R |= 0x20;		//setting RS
	delayms(2);				//delay 2 milliseconds
	GPIO_PORTA_DATA_R |= 0x80;		//setting EN
	GPIO_PORTB_DATA_R = data;		//sending data
	delayms(2);				//delay 2 milliseconds
	GPIO_PORTA_DATA_R &= ~0x80;		//clearing EN
	delayms(2);				//delay 2 milliseconds
}

////     LCD control     ////
void LCD_command(unsigned char command)
{
	GPIO_PORTA_DATA_R &= ~0x20; 		//clearing RS
	delayms(2);				//delay 2 milliseconds
	GPIO_PORTA_DATA_R |= 0x80; 		//setting EN
	GPIO_PORTB_DATA_R = command;		//sending command
	delayms(2);				//delay 2 milliseconds
	GPIO_PORTA_DATA_R &= ~0x80; 		//clearing EN
	delayms(2);				//delay 2 milliseconds
}

////     LCD initialization     ////
void LCD_init()
{
	SYSCTL_RCGCGPIO_R |= 0x03;		//activate PortA & PortB
	while((SYSCTL_PRGPIO_R&0x03) == 0){}	//wait until PortA & PortB are activated
	GPIO_PORTB_LOCK_R = 0x4C4F434B;		//unlock PortB
	GPIO_PORTB_CR_R = 0xFF;			//enable commit on PB0-7
	GPIO_PORTB_AFSEL_R = 0;			//disable alt function on PB0-7
	GPIO_PORTB_PCTL_R  = 0;			//configure PB0-7 as GPIOs		
	GPIO_PORTB_AMSEL_R = 0;			//disable analog function on PB0-7
	GPIO_PORTB_PUR_R = 0;			//disable pull-up resistor on PB0-7
	GPIO_PORTB_DIR_R = 0xFF;		//configure PB0-7 as outputs
	GPIO_PORTB_DEN_R = 0xFF;		//enable digital I/O on PB0-7
	GPIO_PORTA_LOCK_R = 0x4C4F434B;		//unlock PortA
	GPIO_PORTA_CR_R |= 0xA0;		//enable commit on PA5 & PA7
	GPIO_PORTA_AFSEL_R &= ~0xA0;		//disable alt function on PA5 & PA7
	GPIO_PORTA_PCTL_R  &= ~0xA0;		//configure PA5 & PA7 as GPIOs
	GPIO_PORTA_AMSEL_R &= ~0xA0;		//disable analog function on PA5 & PA7
	GPIO_PORTA_PUR_R &= ~0xA0;		//disable pull-up resistor on PA5 & PA7
	GPIO_PORTA_DIR_R |= 0xA0;		//configure PA5 & PA7 as outputs
	GPIO_PORTA_DEN_R |= 0xA0;		//enable digital I/O on PA5 & PA7
	LCD_command(0x20); 			//set 5x7 font size
	LCD_command(0x38);			//8-bit data
	LCD_command(0x02); 			//return cursor home
	LCD_command(0x01);			//clear display
	LCD_command(0x0F);			//diplay on & cursor blinking
	LCD_command(0x30);			//wakeup
}

////     LCD string print     ////
void LCD_string(char *str)
{
	while(*str)
	{
		LCD_data(*str);			//printing character
		delayms(1);			//delay 1 millisecond
		str++;				//pointing to the next character			
	}
}




	void LCD_number(long int number)
		{
			
		uint16_t i=0,auff[20];
			
		if (number<0)
						{
							LCD_data('-');
							number*=(-1);
						}
	
		temp=number;
						
						for(i=0;number!=0;i++)
						{
							auff[i]=temp%10;
							number=number/10;
							temp=number;
						}
							for( ; i!=0 ; --i)
							{
							LCD_data(auff[i-1]+48);
							}	
			}


		char LCD_converter(int value)
				{
					
				uint16_t i=0,buff[20];
					
				if (value<0)
								{
									return('-');
									value*=(-1);
								}
								
				if (value==0) return '0';			
			
				temp=value;
								
								for(i=0;value!=0;i++)
								{
									buff[i]=temp%10;
									value=value/10;
									temp=value;
								}
									for( ; i!=0 ; --i)
									{
									return(buff[i-1]+48);
									}	
					}
		
	int minutes;
	int minutes_tens;
	int minutes_units;
	int seconds;
	int seconds_tens;
	int seconds_units;
	bool close_check;
	char temp_quick_cooking;
		
	void LCD_countdown_display(int value)
	{
		
		minutes = value/60;
		minutes_tens = minutes/10;
		minutes_units = minutes - (minutes_tens*10);
		
		seconds = value - (minutes * 60);
		seconds_tens = seconds/10;
		seconds_units = seconds - (seconds_tens*10);
				
		LCD_data( LCD_converter(minutes_tens) );
		LCD_data( LCD_converter(minutes_units) );
		LCD_data(':');
		LCD_data( LCD_converter(seconds_tens) );
		LCD_data( LCD_converter(seconds_units) );
		close_check = false;
		
		while(minutes_tens>-1)
		{
			GPIO_PORTF_DATA_R |=0x0E;
			while(minutes_units>-1)
			{
				while(seconds_tens>-1)
				{
						while(seconds_units>-1)
						{
											if ( temp_quick_cooking == '0' ) 
											{ if(sw2() == 0x00 && seconds_tens < 5 )
												{
													seconds_tens ++;
													seconds_units++;
												}
											}
								if(sw1() == 0x00)
								{
									delayms(10);
									while(sw1() == 0x00){};
									while((sw1() == 0x10) && (sw2() == 0x01))
									{
										LCD_command(0x01);
										GPIO_PORTF_DATA_R |=0x0E;
										LCD_data( LCD_converter(minutes_tens) );
										LCD_data( LCD_converter(minutes_units) );
										LCD_data(':');
										LCD_data( LCD_converter(seconds_tens) );
										LCD_data( LCD_converter(seconds_units+1) );
										delayms(500);
										GPIO_PORTF_DATA_R &=~0x0E;
										delayms(500);	
									}
									
									if(sw1() == 0x00)
										{
										while(sw1() == 0x00);
										close_check = true;
										temp_quick_cooking = 0;
										seconds_tens = 0;
										minutes_units = 0;
										minutes_tens = 0;
										LCD_command(0x01);
										break;
										}
								}
									GPIO_PORTF_DATA_R |=0x0E;
									LCD_command(0x01);
									LCD_data( LCD_converter(minutes_tens) );
									LCD_data( LCD_converter(minutes_units) );
									LCD_data(':');
									LCD_data( LCD_converter(seconds_tens) );
									LCD_data( LCD_converter(seconds_units) );
									delayms(1000);
									seconds_units--;
								}
					
						seconds_units = 9;
						seconds_tens--;
					}
					seconds_tens = 5;
					minutes_units--;
				}	
			minutes_units = 9;
			minutes_tens--;
			
			temp_quick_cooking = 0;						
			if (close_check == false )
				{
					GPIO_PORTF_DATA_R &=~0x0E;
					complete();
				}
		}		
	}	
