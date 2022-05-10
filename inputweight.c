

		char keypad_input = symbol[j][i];
	
		void desired_weight(char case, int i)
		{
			cooking:
			if (i<=9 && i>=1)
			{
				Clear_LCD();
				LCD_data(i);
				delayms(2000);
				Clear_LCD();
				char cooking_time;
				
				switch(case)
					{
					case 'B' :
					cooking_time = 30 * i
					break;
					case 'C' :
					cooking_time = 12 * i
					break;
					}
				
				delays_display(cooking_time);
				complete();
				}
			else
			{
				Clear_LCD();
				LCD_data('Err');
				delays(2);
				Clear_LCD();
				goto cooking;
			}
		}
		
		void pushB&C()
		{
			
		switch(keypad_input)
		{
			case 'B' :
			LCD_data('Beef Weight?');
			//while(keypad doesn't pressed) {};
			desired_weight('B', keypad_input);
			break;
			case 'B' :
			LCD_data('Chicken Weight?');
			//while(keypad doesn't pressed) {};
			desired_weight('C', keypad_input);
			break;
		}
				
