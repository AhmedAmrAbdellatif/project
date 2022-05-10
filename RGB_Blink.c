void RGB_blinks (unsigned char LED){
GPIO_PORTF_DATA_R |=LED;    //set leds
delayms(500);
GPIO_PORTF_DATA_R &=~LED;   //clear leds
delayms(500);
}

	
	
	
	
