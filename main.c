
void main()
{
	char time[4] = { };	//	time array = 00 00
	unsigned long i, j; //	counters
	
	/////////		take inputs from Key bad and Disply it on LCD		/////////
	for(i=0; i< 4; i++)
	{
		time[0] = keypad_getkey; // new element is placed in t[o]
		if (time[i] >= '0' && time[i] <= '9')	//time must be integer
		{
			//// 	print to LCD minutes		////
			for(j=3; j>1; j--)
			{
					// print to LCD time[x] 
			}
			
			// print to LCD " : "
			
			//// 	print to LCD seconds		////
			for(j=1; j>= 0; j--)
			{
					// print to LCD time[x]
			}
			////			shifting elements of time array			////
			for(j=i; j>=0&&(i+1<4); j--) //stop when you reach t[0] or t[4]
			{
					time[j+1] = time[j];	
			}
		}
		// wrong input
		else // print to LCD " Error "
		
		if (button_2 == 0) // SW 2 is pressed
		{
			// start cooking
		}
	
	}
}
