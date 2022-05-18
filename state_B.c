
void pushB()
		{
		char temp_input;	
		LCD_data('B');                                // print "B" on LCD for 1 sec
		delayms(1000);                   
		clear_LCD;                                   // clear LCD 
		delayms(50);
		question:LCD_string("Beef Weight?");         // print "Beaf weight?" on LCD for 50 ms 
		delayms(50);
		
		temp_input = keypad_input();                 // get input from keypad
		LCD_data(temp_input);	
			
			
		if ( temp_input <='9' && temp_input >='1')  // check if 1<=input<=9   
		{
			

					while (sw2() != 0x00)    // if SW1 is pressed clear LCD in condition not pressing SW2
					{
						if (sw1() == 0x00)
						{
							clear_LCD;
							delayms(50);
							goto question;
						}
					}
					
				delayms(20);                    // SW2 is pressed start operation 
				clear_LCD;
				desired_weight('B', temp_input );		

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
