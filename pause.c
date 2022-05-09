	void pause()
	{
		button_in = SW1_Input();
		while (button_in != 0x10)
		{
			NVIC_ST_CTRL_R &= ~0x1;
		}
	}
