#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Keypad_Init.h"
#include "LCD_Init.h"
#include "Switches.h"
#include "LED.h"
#include "Delay.h"
#include "States.h"
#include "Interrupt.h"
#define CR  0x0D
#include "string.h"


#define buzzer (GPIO_PORTE_DATA_R & 0x20)	
#define external_button (GPIO_PORTE_DATA_R & 0x01)


char timer;



