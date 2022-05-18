////	calculating cooking time in secends	////
unsigned long calc(char time[4])
{
	unsigned long duration = 0;
	long i;
	for (i = 0; i<4 ;i++)	
	{
		time [i] -= '0';	// convert from char --> number
	}
	duration = time[0] + time[1]*10 + time[2]*60 + time[3]*600;   // second units +  second tens + minute units +  minute tens
	return duration;
}

////	clear the LCD then display time on it	////
void print_time (char time[4])
{
	long j; //	counter
	clear_LCD; 
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
void clear_time (char time[4])
{
	long  clear_counter; //	counter
	for (clear_counter=0; clear_counter<4 ; clear_counter++)
	{
		time[clear_counter] = '0';
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
	clear_LCD;	
	LCD_string("Cooking Time?");
	delayms(2000); 		
	
take_input:
	print_time(time);	// 00 : 00
	for(i=0; i< 5; i++)
	{
		
		time_temp = keypad_input();
		
		////	check the switches	////
		if (switch_2)  // SW 2 is pressed start cooking
		{
			switch_2 = false;
			break;						
		}
		
		if (switch_1) 	// SW 1 is pressed clear LCD then restart iterations 
		{
			switch_1 = false;
			i = -1; // first iteration
			clear_time (time); // time = 00:00
			delayms(250);
			print_time(time); // display 00:00	
			continue;
		}
		
		////	take action	////
		delayms(250);
		
		////	  shifting elements of time array before the new entry    ////
		if (time_temp >= '0' && time_temp <= '9')	
		{
			for(j=i-1; j>=0; j--) 
			{
				time[j+1] = time[j];	// 10 minutes <--- 10 minutes <--- 10 Seconds <--- Seconds
			}
			time[0] = time_temp;        // new entry in seconds units 
			print_time(time);
		}
		// wrong input	 print error for 2 sec then retake this input 
		else
		{
			////	check the switches	////
			if (switch_2 == true) goto start_cooking_d;
			if (switch_1 == true) continue;
			
			////	take action	////
			clear_LCD;
			LCD_string("Error");
			delayms(2000);
			print_time(time);
			i--; // repeat this iteration
		}	
	}
	
start_cooking_d:
	clear_LCD;
	pushd_time = calc(time); // calculate time in seconds 
	if (pushd_time > 1800 || pushd_time < 1) // range from  1 second to 30 minutes
	{
		clear_LCD;
		LCD_string("Out of Range");
		delayms(1500);
		if (pushd_time > 1800)
		{
			clear_LCD;	
			LCD_string("Max. 30 minutes");
			delayms(1500);
		}	

		if (pushd_time < 1)
		{
			clear_LCD;	
			LCD_string("Min. 1 second");
			delayms(1500);
		}	

		switch_2 = false;	
		clear_LCD;	
		clear_time(time);
		goto take_input;
	}

	LCD_number( pushd_time );
	LCD_string(" seconds");

	delayms(1500);
	clear_LCD;

	LCD_string("Begin Cooking");

	delayms(1500);
	clear_LCD;
	switch_2 = false;
	switch_1 = false;

	LED_ON;
	LCD_countdown_display(pushd_time);
}
