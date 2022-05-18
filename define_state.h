#define clear_LCD (( LCD_command(0x01) ));
#define LED_ON (GPIO_PORTF_DATA_R |=0x0E);
#define LED_OFF (GPIO_PORTF_DATA_R &=~0x0E);
#define BUZZER_ON (GPIO_PORTE_DATA_R|=0x20);
#define BUZZER_OFF 	(GPIO_PORTE_DATA_R&=~0x20);

unsigned char sw1 (){return GPIO_PORTF_DATA_R & 0x10;}
unsigned char sw2 (){return GPIO_PORTF_DATA_R & 0x01;}
unsigned char sw3 (){return GPIO_PORTE_DATA_R & 0x01;}

#include "stdbool.h"
long cooking_time;
long countdown;
char time_temp;
long clear_counter;
long pushd_time;
bool close_check = false;
char temp_quick_cooking;
