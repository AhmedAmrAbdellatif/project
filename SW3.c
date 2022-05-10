SW3_button = Switch_Input(3);

void resume()
{
NVIC_ST_CTRL_R |= 0x1;
}


void pause()
{
		
while (sw3_button != 0x10)
{
NVIC_ST_CTRL_R &= ~0x1;
}
resume();
}


void sw3_check()
{
if (sw3_button != 0x10)
{
pause();
}
}
