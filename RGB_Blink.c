void RGB_blinks (unsigned char LED){
GPIO_PORTF_DATA_R &=~LED; //clear leds
genericDelay(500);
GPIO_PORTF_DATA_R |=LED; //set leds
genericDelay(500);
}

	
	
	
	
