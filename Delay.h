unsigned long counter_delay;

void SysTick_wait(unsigned long delay)												
{
	NVIC_ST_CTRL_R = 0x00;
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0x00;
	NVIC_ST_CTRL_R |= 0x05;
	while( (NVIC_ST_CTRL_R & 0x00010000) == 0) {
	}
}
