////	calculating cooking time in secends	////
unsigned long calc(char arr[4])
{
    unsigned long duration = 0;
    long i;
    for (i = 0; i<4 ;i++)	// convert from char --> number
    {
        arr [i]= (arr[i] - '0');
    }
    duration = arr[0] + arr[1]*10 + arr[2]*60 + arr[3]*600;
    return duration;
}
void print_time (char time[4])
	{
	long j; //	counter
	//// 	display minutes on LCD 	////
	for(j=3; j>1; j--)
	{
		LCD_data(time[j]); 
	}

	LCD_data(':'); 

	//// 	display seconds on LCD 	////
	for(j=1; j>= 0; j--)
	{
		LCD_data(time[j]); 
	}
}
void PushD()
{
	char time[4] = {'0', '0', '0', '0'};	//	time array = 00 : 00
	long i, j; //	counters
	
	/////////		take inputs from Key bad and Disply it on LCD		/////////
	Clear_LCD();		// clearing the LCD
	LCD_string("Cooking Time?");
	delayms(2000); 		// 2 sec delay
	Clear_LCD();		// clearing the LCD
	print_time(time);	// 00 : 00
	for(i=0; i< 4; i++)
	{
		/*
		// SW 2 is pressed
		if (Switch_Input (2) == 0) 
		{
			break;
		}
		// SW 1 is pressed
		if (Switch_Input (1) == 0) 
		{
			i = -1; // return to first round
			Clear_LCD(); // clear the lcd
			time[4] = {'0', '0', '0', '0'}; 
			print_time(time); // display 00:00	
		}
		*/
		time[0] = keypad_input; // new element is placed in t[o] --> (default : second)
		if (time[i] >= '0' && time[i] <= '9')	//time must be number
		{
			print_time(time);
			////	  shifting elements of time array	////
			for(j=i; j>=0 && (i+1<4); j--) //stop when you reach t[0] or t[3]
			{
				time[j+1] = time[j];	// 10 minutes <--- 10 minutes <--- 10 Seconds <--- Seconds
			}
		}
		// wrong input	 print error for 2 sec then retake this input & decrement i
		else
		{
			Clear_LCD();
			LCD_string("error");
			delayms(2000);
			Clear_LCD();
			print_time(time);
			i--;
		}
	}
	LCD_number(calc(time));
}
