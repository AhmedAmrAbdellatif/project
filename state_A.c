void pushA()
      {
	LCD_data('A');  //show 'A' on LCD
	delayms(500);	//show 'A' on LCD for (0.5sec)
	clear_LCD;
	delayms(500);
	LCD_string("Popcorn");
	delayms(2000);
	clear_LCD;

	LCD_countdown_display(60);
       }
