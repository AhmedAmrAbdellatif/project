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
