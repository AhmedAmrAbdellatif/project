///////In progress///////

  void SW2_check_forcooking()
{
  while((GPIO_PORTF_DATA_R & 0x01) == 0x01){}    //Acting like a delay waiting the user to push SW2 to start cooking "go out from the funtion".
}
  
  //To start cooking after SW2 is pushed (=0x00), i suggest to check SW2 in " delays_display " function before go on the "for" loop.
  
  int delays_display(unsigned long time)												
		{
    LCD_data (counter);
    SW2_check_forcooking();
		for (counter=time; counter>=0; counter--)			
		{
			LCD_data (counter);
			delayms(1000);
			SW3_check();      //cheak if sw3 is pressed(door is open)
			SW1_check();      //cheak if sw1 is pressed
		}
		 counter = 0;
     complete();
		}
