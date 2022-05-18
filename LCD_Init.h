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
}
