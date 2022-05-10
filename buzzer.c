 void buzzer()
	{
		GPIO_PORTX_DATA_R|=0x01; //buzzer pin
	}