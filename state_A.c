void pushA()
      {
	LCD_data('A');
	delayms(500);
	clear_LCD;
	delayms(500);
	LCD_string("Popcorn");
	delayms(2000);
	clear_LCD;

	LCD_countdown_display(60);
       }
