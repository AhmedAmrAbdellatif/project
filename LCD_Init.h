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
