voltaile unsigned long FallingEdges = 0;  "global" //Acts like a counter. 
//PortF SW1-SW2 Interrupt Initialization//
FallingEdges = 0;             //After portF clock enable
GPIO_PORTF_IS_R &= ~0x11;     // PF4-0 is edge-sensitive
GPIO_PORTF_IBE_R &= ~0x11;   // PF4-0 is not both edges
GPIO_PORTF_IEV_R &= ~0x11;   // PF4-0 falling edge event 
GPIO_PORTF_ICR_R = 0x11;     // clear flag4
GPIO_PORTF_IM_R |= 0x11;     // arm interrupt on PF4-0
//NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;  //(g) priority 5 "can be changed" - OPTIONAL
NVIC_EN0_R = 0x40000000;     // enable interrupt 30 "Port F" in NVIC
EnableInterrupts();         // Enable global Interrupt flag (I)


//Function////InProgress//
  
void GPIOPortF_Handler(void){
SW3_button = Switch_Input(3);
if(SW3_button == 1) {            //check that the door is closed 
  if(GPIO_PORTF_MIS_R & 0x10)   //check if interrupt causes by PF4/SW1
  {     
    GPIO_PORTF_ICR_R = 0x10;   // clear the interrupt flag 
    if(FallingEdges ==1 )      //pressed for the second time
    {
       FallingEdges =0;        //clear the counter
       /*"stop cooking"
	 NVIC_ST_CTRL_R &= ~0x1;
	LCD_command(0x01); */		
		}
       else if((FallingEdges=0) && (counter !=0))  //if pressed SW1 at (first time && during cooking)
       {
	 
         FallingEdges ++;                          //FallingEdges=1
	 counter_handler=counter;
           /*"pause cooking"
	     NVIC_ST_CTRL_R &= ~0x01;
	      LCD_command(0x01);
	      LCD_data(counter)*/
       }
	 else if((FallingEdges=0) && (counter=0))  //pressed SW1 in case 'D' before start cooking so counter is still = 0
		 {
		   /*LCD_command(0x01);*/
		 }
		 
	 }
   else if (GPIO_PORTF_MIS_R & 0x01)   //check if interrupt causes by PF0/SW2
   {
      GPIO_PORTF_ICR_R = 0x01;         //clear the interrupt flag 
      if(FallingEdges ==1)             //pressed SW2 in pausing state 
	 {
	 FallingEdges =0;
	 /*"resume cooking"
	  LCD_command(0x01);
	   delays_display(counter);
	   complete();*/   
	      
	 }
	else if(FallingEdges ==0 && (calc(time) != 0))   //pressed SW2 to start cooking for case 'D'
		{
			 /*"start cooking for case 'D' "
			 delays_display(calc(time));
			 complete();*/    
		 }
			 
	 }
 }
else if(SW3_button == 0){}     //the door is open
}



