unsigned char sw1 (){return GPIO_PORTF_DATA_R & 0x10;}
unsigned char sw2 (){return GPIO_PORTF_DATA_R & 0x01;}
unsigned char sw3 (){return GPIO_PORTE_DATA_R & 0x01;}



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
	
long kk;
long pushd_time;

void pushD()
{
	char time[4] = {'0', '0', '0', '0'};	//	time array = 00 : 00
	long i, j; //	counters

	DisableInterrupts();
	
	LCD_data('D');
	delayms(500);
	clear_LCD;
	delayms(2);

	/////////    take inputs from Key bad and Disply it on LCD	/////////
	clear_LCD;		// clearing the LCD
	LCD_string("Cooking Time?");
	delayms(1000); 		// 1 sec delay
	clear_LCD;		// clearing the LCD
	
	print_time(time);	// 00 : 00
	for(i=0; i< 4; i++)
	{
		// SW 2 is pressed
		if (sw2 () == 0) 
		{
			break;						
		}
		// SW 1 is pressed
		if (sw1 () == 0) 
		{
			i = -1; // return to first round
			clear_LCD; // clear the lcd
			for (kk=0; kk<4 ; kk++)
			{
			time[kk] = '0';
			}
			print_time(time); // display 00:00	
		}
		
		time_temp = keypad_input();
		delayms(200);
		if (time_temp >= '0' && time_temp <= '9')	//time must be number
		{
			////	  shifting elements of time array	////
			for(j=i-1; j>=0; j--) 
			{
				time[j+1] = time[j];	// 10 minutes <--- 10 minutes <--- 10 Seconds <--- Seconds
			}
			time[0] = time_temp;
			clear_LCD;
			print_time(time);
		}
		// wrong input	 print error for 2 sec then retake this input & decrement i
		else
		{
			clear_LCD;
			LCD_string("error");
			delayms(2000);
			clear_LCD;
			print_time(time);
			i--;
		}
	}
start_cooking_d:
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
	
	LED_ON;
					
	for (countdown=pushd_time;countdown>0;countdown--)
	{
		LED_ON;	
		LCD_number(countdown);
		delayms(1000);
		clear_LCD;
	}
						
	GPIO_PORTF_DATA_R &=~0x0E;	
	complete();

				
}
		
