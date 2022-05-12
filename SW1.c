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
  if(GPIO_PORTF_MIS_R & 0x10)   //check if interrupt causes by PF4/SW1
  {     
    GPIO_PORTF_ICR_R = 0x10;   // clear the interrupt flag 
    if(FallingEdges ==1 )      //FallingEdges is initialized by '0'
    {
       FallingEdges =0;        //clear the counter
       LCD_clear;              //Stop
       else
       {
         FallingEdges ++;     //FallingEdges=1
         pause;               //pause cooking
       }
		 }
	 else if (GPIO_PORTF_MIS_R & 0x01)   //check if interrupt causes by PF0/SW2
		  GPIO_PORTF_ICR_R = 0x01;         // clear the interrupt flag 
     if(FallingEdges ==1)              //to make sure that we are pasuing cooking
		 {
			 resume();                       //resume cooking
		 }
	}
}
    
    

 



