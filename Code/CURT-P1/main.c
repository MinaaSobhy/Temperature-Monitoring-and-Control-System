
#include "main.h"




void main()
{
	// ADC For Temperature Sensor Configuration
	ADC_ConfigType ADC_Config = {INTERNAL_VOLTAGE, F_CPU_8};
	ADC_init (&ADC_Config);

	//send the channel number in which LM35 is connected
	ADC_read(ADCchannel);

	//LCD Initialization
	LCD_init();

	//DC motor Initialization
	DCmotor_init();

	//LED initialization
	GPIO_setupPinDirection(LEDR_PORT,LEDR_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDY_PORT,LEDY_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDG_PORT,LEDG_PIN, PIN_OUTPUT);
	//Buzzer initialization
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN, PIN_OUTPUT);
	//Push button initialization
	GPIO_setupPinDirection(BUTTON_PORT,BUTTON_PIN, PIN_INPUT);

	/* Set the three bits to turn off the LEDs at the beginning */
	GPIO_writePin(LEDR_PORT,LEDR_PIN, LOGIC_HIGH);
	GPIO_writePin(LEDY_PORT,LEDY_PIN, LOGIC_HIGH);
	GPIO_writePin(LEDG_PORT,LEDG_PIN, LOGIC_HIGH);
	//Set the buzzer to low value to be initially stopped
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);

	//define variable to store the current temperature
	uint8 temp;

	while (1)
	{
		//store the current temperature in the variabel
		temp = LM35_getTemp();

		//start to print the titles
		LCD_moveCursor(0,0);
		LCD_displayString("Temp =      C");

		//print the current temperature
		LCD_moveCursor(0,8);
		LCD_intgerToString(temp);

//		it is not required as a condition but it can be add for corner cases
//		if (temp < 0)
//		{
//			/*if the temperature is bellow the 0, so, there is an error
//			 *in the system print error for the user */
//			LCD_moveCursor(1,0);
//			LCD_displayString("    ERROR   ");
//		}

		if ( temp < 20)
		{
			/* if the temperature is below 20 the green led
			 * will lighten up and the motor and buzzer will be stop
			 * if they are running
			 */
			GPIO_writePin(LEDR_PORT,LEDR_PIN, LOGIC_HIGH);
			GPIO_writePin(LEDY_PORT,LEDY_PIN, LOGIC_HIGH);
			GPIO_writePin(LEDG_PORT,LEDG_PIN, LOGIC_LOW);

			GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);

			DCmotor_info(STOP,'F');

		}
		else if ( temp < 40)
		{
			/* if the temperature is equal 20 and below the 40
			 * the yellow led will lighten and the motor will run
			 * with a speed depending on the temperature start from zero when
			 * temperature is equal to 19 and its speed increase 4.75% every
			 * degree till reaching 100% at temperature 40 and buzzer will be stop
			 * if it was running
			 */
			GPIO_writePin(LEDR_PORT,LEDR_PIN, LOGIC_HIGH);
			GPIO_writePin(LEDY_PORT,LEDY_PIN, LOGIC_LOW);
			GPIO_writePin(LEDG_PORT,LEDG_PIN, LOGIC_HIGH);

			GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_LOW);

			/*send the current temperature and the set the motor
			to always rotate ACW (Forward) to push the air*/
			DCmotor_info(temp,'F');

		}
		else
		{
			/*enter a loop if temperature is more than or equal 40
			 * and remain in the loop until both the push button is pressed and
			 * the temperature is below 40
			 */
			while(1)
			{
				temp = LM35_getTemp();
				LCD_moveCursor(0,8);
				LCD_intgerToString(temp);
				//print warning on the screen
				LCD_moveCursor(1,0);
				LCD_displayString("    WARNING!   ");

				//activating the red led
				GPIO_writePin(LEDR_PORT,LEDR_PIN, LOGIC_LOW);
				GPIO_writePin(LEDY_PORT,LEDY_PIN, LOGIC_HIGH);
				GPIO_writePin(LEDG_PORT,LEDG_PIN, LOGIC_HIGH);
				//activating the buzzer
				GPIO_writePin(BUZZER_PORT,BUZZER_PIN, LOGIC_HIGH);

				/*set the motor to rotate with maximum value and
				 *set the motor to always rotate ACW (Forward) to
				 *push the air*/
				DCmotor_info(MAX,'F');

				//check if the button is pressed
				if(GPIO_readPin(BUTTON_PORT,BUTTON_PIN))
				{
					//if yes, so delay for 30 sec to avoid debouncing
					_delay_ms(30);
					/*check again for the button and temperature so that if
					they are true exit the loop*/
					if (GPIO_readPin(BUTTON_PORT,BUTTON_PIN) && temp <40)
					{
						break;
					}

				}
			}
			//clear the screen from the warning
			LCD_clearScreen();

		}

	}
}




