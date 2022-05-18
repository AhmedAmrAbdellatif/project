void complete()
{				
				clear_LCD;
				delayms(1);
				LCD_data('0');
				LCD_data('0');
				LCD_data(':');
				LCD_data('0');
				LCD_data('0');
	
				blink_buzzer(3);
	
				BUZZER_OFF; //clear buzzer pin
				LED_OFF; //clear leds	
				delayms(100);
				clear_LCD;
	
}				
