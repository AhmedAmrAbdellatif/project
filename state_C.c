
void pushC()
		{
			
		char temp_input;
	
		LCD_data('C');
		delayms(1000);
		clear_LCD;
		delayms(50);
		question:LCD_string("Chicken Weight?");
		delayms(50);
		
		temp_input = keypad_input();
		LCD_data(temp_input);	
			
			
		if ( temp_input <='9' && temp_input >='1')
		{
			

					while (sw2() != 0x00)
					{
						if (sw1() == 0x00)
						{
							clear_LCD;
							delayms(50);
							goto question;
						}
					}
					
				delayms(20);
				clear_LCD;
				desired_weight('C', temp_input );		

		}
		
		else
			{
				clear_LCD;
				LCD_string("Invalid Input");
				delayms(1500);
				clear_LCD;
				LCD_string("Only Between 1:9");
				delayms(1500);
				clear_LCD;
				goto question;
			}				
		}
