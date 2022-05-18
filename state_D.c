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
