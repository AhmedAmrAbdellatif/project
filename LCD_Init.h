void LCD_data(unsigned char data)
{
	//GPIO_PORTA_DATA_R &= ~0x40;		// R/W will be connected to the GND externally
	GPIO_PORTA_DATA_R |= 0x20;
	delayms(2);
	GPIO_PORTA_DATA_R |= 0x80;
	GPIO_PORTB_DATA_R = data;
	delayms(2);
	GPIO_PORTA_DATA_R &= ~0x80;
	delayms(2);
}
