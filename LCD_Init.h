////     PortA (Pin5->RS)(Pin7->EN) & PortB (Pin0-7->D0-7)     ////

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
	SYSCTL_RCGCGPIO_R |= 0x03;
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
