
void quick_cooking()
{
		temp_quick_cooking = '0';
		LCD_data('0');
		delayms(200);
		clear_LCD;
		delayms(500);
		LCD_string("Quick Cooking");
	 	delayms(1000);
		clear_LCD;

		LCD_countdown_display(10);
	
		temp_quick_cooking = 0;
}
