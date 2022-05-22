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
void LEDSW_Init()
{
	SYSCTL_RCGCGPIO_R	|= 0x20;		//PORT F Clock enable

	while ( (SYSCTL_PRGPIO_R&0x20) == 0) {}		

	GPIO_PORTF_LOCK_R |= 0x4C4F434B;		//Unlock PORT F
	GPIO_PORTF_CR_R |= 0x1F;			//Allow changes to pins 0,1,2,3,4
	GPIO_PORTF_DIR_R |= 0x0E;			//SET pins 1,2,3 to be output
	GPIO_PORTF_DIR_R &= ~0x11;			//SET pins 0,4 to be input
	GPIO_PORTF_DEN_R |= 0x1F;			//SET pins 0,1,2,3,4 to be digital
	GPIO_PORTF_AMSEL_R &= ~0x1F;			//Disable Analog function
	GPIO_PORTF_AFSEL_R &= ~0x1F;			//No alternative function
	GPIO_PORTF_PCTL_R &= ~0xFFFFF;			//GPIO clear bit PCTL
	GPIO_PORTF_DATA_R &= ~0x0E;			//Initialize LEDs to be off
	GPIO_PORTF_PUR_R |= 0x11;			//SET pull-up resistance
}

char turn;                                              // counter value 

 void blink_buzzer(unsigned char n)                     // Blink both buzzer and leds (n) times 
	{
		for(turn=0; turn<n; turn++)
		{
		GPIO_PORTE_DATA_R |=0x20;               //buzzer pin5 on
		GPIO_PORTF_DATA_R |=0x0E;		//Array of led on 
		delayms(500);
		GPIO_PORTE_DATA_R &=~0x20;              //buzzer pin5 off
		GPIO_PORTF_DATA_R &=~0x0E;              //Array of led off 
		delayms(500);
		}
 void blink()                                           //Blink leds 
	{
	GPIO_PORTF_DATA_R |=0x0E;		        //Array of led on
	delayms(500);
	GPIO_PORTF_DATA_R &=~0x0E;                      //Array of led off
	delayms(500);
	}	
	

