void sw3_buzzer_init()
{
	SYSCTL_RCGCGPIO_R	|= 0x10;		//PORT E Clock enable
	while ( (SYSCTL_PRGPIO_R&0x10) == 0) {}		
	GPIO_PORTE_DIR_R &= ~0x01;			//SET pin 0 sw3 to be input 
	GPIO_PORTE_DIR_R |= 0x20;			//SET pin 5 buzzer to be output
	GPIO_PORTE_DEN_R |= 0x21;			//SET pins 0,5 to be digital
	GPIO_PORTE_AMSEL_R &= ~0x21;			//Disable Analog function
	GPIO_PORTE_AFSEL_R &= ~0x21;			//No alternative function
	GPIO_PORTE_PCTL_R &= ~0xFFFFF;			//GPIO clear bit PCTL
	GPIO_PORTE_DATA_R &= ~0x20;			//Initialize BUZZER to be off
	GPIO_PORTE_PDR_R |= 0x01;			//SET pull-down resistance FOR sw3   0 is open door , 1 is closed door
}

