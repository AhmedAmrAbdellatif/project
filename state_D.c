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

void pushD()
{
	char time[4] = {'0', '0', '0', '0'};	//	time array = 00 : 00
	long i, j; //	counters
	switch_2 = false;
	switch_1 = false;
	/////////    display option D	/////////
	LCD_data('D');
	delayms(800);
	clear_LCD;
	delayms(2);
	
	/////////    take inputs from Key bad and Disply it on LCD	/////////
	clear_LCD;		// clearing the LCD
	LCD_string("Cooking Time?");
	delayms(2000); 		// 1 sec delay
	clear_LCD;		// clearing the LCD
	
take_input:
	print_time(time);	// 00 : 00
	for(i=0; i< 5; i++)
	{
		
		// SW 2 is pressed start cooking
		if (switch_2) 
		{
			switch_2 = false;
			break;						
		}
		
		time_temp = keypad_input();
		
		// SW 1 is pressed clear LCD then return to the first iteration
		if (switch_1) 
		{
			switch_1 = false;
			i = -1; // first iteration
			clear_LCD; // clear the lcd
			for (clear_counter=0; clear_counter<4 ; clear_counter++)
			{
				time[clear_counter] = '0';
			}
			delayms(250);
			print_time(time); // display 00:00	
			continue;
		}
		
		delayms(250);
		
		////	  shifting elements of time array before the new entry    ////
		if (time_temp >= '0' && time_temp <= '9')	//time must be number
		{
			for(j=i-1; j>=0; j--) 
			{
				time[j+1] = time[j];	// 10 minutes <--- 10 minutes <--- 10 Seconds <--- Seconds
			}
			time[0] = time_temp;        // new entry in seconds units 
			clear_LCD;
			print_time(time);
		}
