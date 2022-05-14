
long check_counter;
char keypad_check()					
{
	char checker = 1;
 	while(1)		
	{
		for(check_counter = 0; check_counter < 4; check_counter++)	//scan rows
				{
					if( (GPIO_PORTE_DATA_R & 0x1E) & (1 << (check_counter+1) ) )
					{
						checker = 0;
						return checker;
					}
					
				}
	}
}


void pushD()
{
	
	

	char time[4] = {'0', '0', '0', '0'};	//	time array = 00 : 00
	long i, j; //	counters
	
	DisableInterrupts();
	
		LCD_data('D');
		delayms(500);
		clear_LCD;
		delayms(2);
	
	/////////		take inputs from Key bad and Disply it on LCD		/////////
	clear_LCD;		// clearing the LCD
	LCD_string("Cooking Time?");
	delayms(1000); 		// 1 sec delay
	clear_LCD;		// clearing the LCD
	
	print_time(time);	// 00 : 00
	for(i=0; i< 4; i++)
	{
		
		// SW 2 is pressed
		if (Switch_Input (2) != 0x01) 
		{
			break;						
		}
		// SW 1 is pressed
		if (Switch_Input (1) != 0x10) 
		{

			i = -1; // return to first round
			clear_LCD; // clear the lcd
		

			for (kk=0; kk<4 ; kk++)
			{
			time[kk] = '0';
			}
			print_time(time); // display 00:00	
		}
		
		
		while(keypad_check());
		
			////	  shifting elements of time array	////
			for(j=i; j>=0 && (i<4); j--) //stop when you reach t[0] or t[3]
			{
				time[j+1] = time[j];	// 10 minutes <--- 10 minutes <--- 10 Seconds <--- Seconds
			}
			
		time[0] = keypad_input(); // new element is placed in t[o] --> (default : second)
			
		
			
		if (time[0] >= '0' && time[0] <= '9')	//time must be number
		{
			clear_LCD;
			print_time(time);
		}
		// wrong input	 print error for 2 sec then retake this input & decrement i
		else
		{
			clear_LCD;
			LCD_string("Error");
			time[0] = time[1];
			time[1] = time[2];
			time[2] = time[3];
			
			if (i==3) {time[3] ='0';}
			
			delayms(2000);
			clear_LCD;
			
			print_time(time);
			i--;
		}
	}
	
	clear_LCD;
	
	print_time(time);
	delayms(500);
	
	clear_LCD;
	EnableInterrupts();
	pushd_time = calc(time);
	LCD_number( pushd_time );
	LCD_string(" seconds");

	delayms(1000);
	clear_LCD;
	
	LCD_string("Begin Cooking");

	delayms(1000);
	clear_LCD;
	
	GPIO_PORTF_DATA_R |=0x0E;
					
	for (countdown=pushd_time;countdown>0;countdown--)
	{
		GPIO_PORTF_DATA_R |=0x0E;	
		LCD_number(countdown);
		delayms(1000);
		clear_LCD;
	}
						
	GPIO_PORTF_DATA_R &=~0x0E;	
	complete();

				
}
