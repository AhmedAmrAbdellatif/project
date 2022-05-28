void pushA()
{
	 LCD_data('A');  		//show 'A' on LCD
	 delayms(500);			//show 'A' on LCD for (0.5sec)
	 clear_LCD;			//clear LCD
	 delayms(500);			//delay(0.5)

	 /////////showing popcorn///////////

	 LCD_string("Popcorn");		//show 'A' on LCD
		delayms(500);

	while (sw2() != 0x00)														
	{														
		if (sw1() == 0x00)
		{
			clear_LCD;
			delayms(50);
			return;
		}
	}																								
	 clear_LCD;			//clear LCD

	 //////////countdown///////////

	 LCD_countdown_display(60);	//countdown(60 sec)
}
