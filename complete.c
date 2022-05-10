void complete(){
		
		LCD_Clear();
		for(int i=0; i<3; i++)
		{
		buzzer();
		RGB_blinks(0x0E);
		}
		GPIO_PORTX_DATA_R&=~0x01; //clear buzzer pin
	        GPIO_PORTF_DATA_R&=~0E; //ckear leds
	}
