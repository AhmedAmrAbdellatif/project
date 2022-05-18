void LCD_data(unsigned char data)
{
	GPIO_PORTA_DATA_R |= 0x20;		// RS = 1
	delayms(2);				//delay 2 milliseconds
	GPIO_PORTA_DATA_R |= 0x80;		// EN = 1
	GPIO_PORTB_DATA_R = data;
	delayms(2);				//delay 2 milliseconds
	GPIO_PORTA_DATA_R &= ~0x80;		// EN = 0
	delayms(2);				//delay 2 milliseconds
}
