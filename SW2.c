SW2_button = Switch_Input(2);
void SW2_check()
{
if (SW2_button != 0x01)
{
start();
}
