void Interrupt_Init()          
	{
	DisableInterrupts();		     //Disable global Interrupts flag initially
	
	SYSCTL_RCGCGPIO_R	|= 0x10;     //PORT E Clock enable

	while ( (SYSCTL_PRGPIO_R&0x10) == 0) {}	

		GPIO_PORTE_IS_R |= 0x1;      //PE0 is edge-sensitive
		GPIO_PORTE_IBE_R |= 0x0;     //PE0 is not both edges
		GPIO_PORTE_IEV_R |= 0x1;     //PE0 falling edge event
		GPIO_PORTE_ICR_R = 0x1;      //clear flag0
		GPIO_PORTE_IM_R |= 0x1;      //arm interrupt on PE0
		
	NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000040;  
	NVIC_EN0_R = 0x10;                   //Enable interrupt 4 in NVIC
		
	}


void GPIOPortE_Handler(void)
{
	GPIO_PORTE_ICR_R = 0x1;   // acknowledge flag0
	blink();
}
