////	calculating cooking time in secends	////
unsigned long calc(char arr[4])
{
    unsigned long duration = 0;
    unsigned long i;
    for (i = 0; i<4 ;i++)	// convert from char --> number
    {
        arr [i]= (arr[i] - '0');
    }
    duration = arr[0] + arr[1]*10 + arr[2]*60 + arr[3]*600 ;
    return duration;
}
void main()
{
	char time[4] = {'0', '0', '0', '0'};	//	time array = 00 00
	long i, j; //	counters
	
	/////////		take inputs from Key bad and Disply it on LCD		/////////
	for(i=0; i< 4; i++)
	{
		// SW 2 is pressed
		if (Switch_Input (2) == 0) 
		{
			break;
		}
		time[0] = keypad_getkey; // new element is placed in t[o]
		if (time[i] >= '0' && time[i] <= '9')	//time must be integer
		{
			//// 	print to LCD minutes	////
			for(j=3; j>1; j--)
			{
				LCD_data(time[j]); 
			}
			
			LCD_data(':'); 
			
			//// 	print to LCD seconds	////
			for(j=1; j>= 0; j--)
			{
				LCD_data(time[j]); 
			}
			////		shifting elements of time array		////
			for(j=i; j>=0&&(i+1<4); j--) //stop when you reach t[0] or t[4]
			{
					time[j+1] = time[j];	
			}
		}
		// wrong input
		else LCD_data("err"); 
		
		
	
	}
	delays_display(calc(time));
}
