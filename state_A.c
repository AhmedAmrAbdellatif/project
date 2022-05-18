void pushA()
{
 LCD_data('A');  		//show 'A' on LCD
 delayms(500);			//show 'A' on LCD for (0.5sec)
 clear_LCD;			//clear LCD
 delayms(500);			//delay(0.5)

 /////////showing popcorn///////////

 LCD_string("Popcorn");		//show 'A' on LCD
 delayms(2000);			//show 'A' on LCD for (2sec)
 clear_LCD;			//clear LCD

 //////////countdown///////////

 LCD_countdown_display(60);	//countdown(60 sec)
}
