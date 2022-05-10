void complete(){
		
		LCD_Clear();
		for(int i=0; i<3; i++)
		{
		buzzer();
		RGB_blinks(0x0E);
		}
		GPIO_PORTE_DATA_R&=~0x20; //clear buzzer pin
	        GPIO_PORTF_DATA_R&=~0x0E; //ckear leds
	}
