
void desired_weight(char state, char weight)
		{
			switch(state)
			{
			case 'B' :
			cooking_time = 30 * (weight-'0');
			break;
			case 'C' :
			cooking_time = 12 * (weight-'0');
			break;
			}
			
			LCD_countdown_display(cooking_time);
		}
		
