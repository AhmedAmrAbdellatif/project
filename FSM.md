enum s{Idle0 ,popcorn1 ,beef2 ,chicken3 ,chooseTime4 ,selectWeight5 , writeTime6 ,pause7 ,cont_count8} //state

Inputs{keypad_input , sw1 ,sw2 ,sw3}  //input
outputs{LCD_display ,countdown}  //output
variables{weightSelected ,totalTime_B ,totalTime_C, beefORchicken, counter}  //variable



void FSM()
{
  enum s state = 0; //(=idle)
  while(1)
  {
    switch(state)
    {
      0:
         LCD_display='Enter choice';      //show (enter choice) on LCD
         if(Keypad_input='A'){state=1;}
         if(Keypad_input='B'){state=2;}
         if(Keypad_input='C'){state=3;}
         if(Keypad_input='D'){state=4;}
         break;
      
      1: i0='A';                 //keypad_input
         LCD_display='popcorn';
         countdown=60;                //countdown
         if(sw1_check==0){state=7; counter=countdown;}
         if(sw3_check==0){state=7; counter=countdown;}
         if(countdown=0){state=0;}
         break;
     
     2: 
        beefORchicken='B';
        LCD_display='beef';
        state=5;
        break;
        
     3: 
        LCD_display='chicken';
        state=5;
        break;
        
     4: 
        LCD_display='cookingTime?';
        state=6;
        break;
        
     5:
       weightSelected=keypad_input
       totalTime_B= V0 * 30;
       totalTime_C= V1 * 12;
       if(v3=='B'){countdown=totalTime_B;}
         else{countdown=totalTime_C;}
       if(V0==0|V0>9){state=s5; break;}
       if(sw1_check==0){state=7; counter=countdown;}
       if(sw3_check==0){state=7; counter=countdown;}
       if(countdown=0){state=0;}
       break;
        
        
     6:
       if(sw1_check==0){state=6; break;}
       if(sw3_check==0){state=7; counter=countdown;}
       if(countdown=0){state=0;}
       break:
    
    7:
      if(sw3_cheak==1 & sw2_check==0){state=s8;}
      break;
       
    8:
      countdown = counter;
      if(sw1_check==0){state=7; counter=countdown;}
      if(sw3_check==0){state=7; counter=countdown;}
      if(countdown=0){state=0;}
      break;
    
    }
  }
}
