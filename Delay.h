unsigned long counter_delay;

////	main delay block	/////
void SysTick_wait(unsigned long delay)												
{
	NVIC_ST_CTRL_R = 0x00;				//disable the systick
	NVIC_ST_RELOAD_R = delay-1;			//entering the counting value
	NVIC_ST_CURRENT_R = 0x00;			//clearing the current value
	NVIC_ST_CTRL_R |= 0x05;				//enable the systick & setting clock source bit 
	while( (NVIC_ST_CTRL_R & 0x00010000) == 0) {}	//checking for count bit
}

////	delay 1 m Sec	/////
void delayms(unsigned long time)
{
	for (counter_delay=0; counter_delay<time ; counter_delay++)
	{
		SysTick_wait(16000);																																										
	}
}
