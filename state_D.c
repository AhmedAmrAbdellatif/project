unsigned char sw1 (){return GPIO_PORTF_DATA_R & 0x10;}
unsigned char sw2 (){return GPIO_PORTF_DATA_R & 0x01;}
unsigned char sw3 (){return GPIO_PORTE_DATA_R & 0x01;}

bool switch_2 = 0;
bool switch_1 = 0;
char time_temp;
		
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
////	 minutes : seconds	////
void print_time (char time[4])
{
	long j; //	counter
	for(j=3; j>1; j--) 	// minutes
	{
		LCD_data(time[j]); 
	}

	LCD_data(':'); 

	
	for(j=1; j>= 0; j--)	// seconds
	{
		LCD_data(time[j]); 
	}
}
	
long kk;
long pushd_time; 

void pushD()
{
	long i, j; //	counters
	LCD_data('D');
	delayms(500);
	clear_LCD;
	delayms(2);
	clear_LCD;	
	LCD_string("Cooking Time?");
	delayms(1000); 
take_input:
	char time[4] = {'0', '0', '0', '0'};	//	time array = 00 : 00
	clear_LCD;	
	print_time(time);	// 00 : 00
	
	for(i=0; i< 4; i++)
	{	
		time_temp = keypad_input();
		// SW 2 is pressed
		if (switch_2) 
		{
			switch_2 = false;
			break;						
		}
		// SW 1 is pressed
		if (switch_1) 
		{
			switch_1 = false;
			i = -1; // return to first round
			clear_LCD; // clear the lcd
			for (kk=0; kk<4 ; kk++)
			{
			time[kk] = '0';
			}
			print_time(time); // display 00:00	
			continue;
		}
		delayms(300);
		if (time_temp >= '0' && time_temp <= '9')	//time must be number
		{
			
			for(j=i-1; j>=0; j--) // shifting elements of time array before new entry 
			{
				time[j+1] = time[j];	// 10 minutes <--- 10 minutes <--- 10 Seconds <--- Seconds
			}
			
			time[0] = time_temp; // new entry is second by defualt
			clear_LCD;
			print_time(time);
		}
		// wrong input	 print error for 2 sec then retake this input & decrement i
		else
		{
			if (switch_2 == true) goto start_cooking_d;
			if (switch_1 == true) continue;
			clear_LCD;
			LCD_string("Error");
			delayms(2000);
			clear_LCD;
			print_time(time);
			i--;
		}
	}
start_cooking_d:
	clear_LCD;
	pushd_time = calc(time);
	if (pushd_time > 1800 || pushd_time < 1) // maximum time 30 minutes = 1800 sec minimum time 1 second 
	{
		clear_LCD;
		LCD_string("Error");
		delayms(2000);
		goto take_input;
	}
	LCD_number( pushd_time );
	LCD_string(" seconds");

	delayms(1000);
	clear_LCD;
	
	LCD_string("Begin Cooking");

	delayms(1000);
	clear_LCD;
	
	LED_ON;
	
	delay_display_complete(pushd_time);
	
	/*for (countdown=pushd_time;countdown>0;countdown--)
	{
		LED_ON;	
		LCD_number(countdown);
		delayms(1000);
		clear_LCD;
	}*/
						
	GPIO_PORTF_DATA_R &=~0x0E;	
	complete();
	switch_2 = false;
	switch_1 = false;

				
}
		
