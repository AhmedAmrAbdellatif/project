//PortF Interrupt Initialization//

GPIO_PORTF_IS_R &= ~0x10;     // PF4 is edge-sensitive
GPIO_PORTF_IBE_R &= ~0x10;   // PF4 is not both edges
GPIO_PORTF_IEV_R &= ~0x10;   // PF4 falling edge event 
GPIO_PORTF_ICR_R = 0x10;     // clear flag4
GPIO_PORTF_IM_R |= 0x10;     // arm interrupt on PF4
//NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;  //(g) priority 5 "can be changed" - OPTIONAL
NVIC_EN0_R = 0x40000000;     // enable interrupt 30 "Port F" in NVIC
EnableInterrupts();         // Enable global Interrupt flag (I)


//Function////InProgress//
//IF SW1 pressed twice//

char FallingEdges = 0;  "global" //Acts like a counter.  
void GPIOPortF_Handler(void){
 GPIO_PORTF_ICR_R = 0x10; // acknowledge flag4
if(FallingEdges ==1 ){
  FallingEdges ==0;
  LCD_clear;  //Stop
}
else
{
FallingEdges ++;
pause;
}
  }



