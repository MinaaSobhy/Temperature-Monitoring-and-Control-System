
#include "lm35.h"



/*
 * Description :
 * Calculate the temperature from the ADC digital value and return it to the user.
 */
uint8 LM35_getTemp(void)
{
	uint8 temp = 0;

	uint16 adc = 0;

	/* Read ADC channel where the temperature sensor is connected */

	adc = ADC_read(SENSOR_CHANNEL_ID);
	_delay_ms(5);
	/* Calculate the temperature from the ADC value*/
	temp = (uint8)(((uint32)adc*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp;
}


