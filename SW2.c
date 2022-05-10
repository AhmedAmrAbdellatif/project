//In progress
SW2_button = Switch_Input(2);
void SW2_check()
{
While (SW2_button != 0x01)
{
Clear_LCD();
delays_display(cooking_time);
complete();
}
