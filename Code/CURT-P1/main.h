

#ifndef MAIN_H_
#define MAIN_H_


#include "std_types.h"
#include "adc.h"
#include "DCmotor.h"
#include "lcd.h"
#include "lm35.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//define the pin in which the sensor is connected in PORTA
#define ADCchannel 0


//Define LED ports
#define LEDR_PORT PORTD_ID
#define LEDY_PORT PORTD_ID
#define LEDG_PORT PORTD_ID
//Define LED pins
#define LEDR_PIN PIN4_ID
#define LEDY_PIN PIN3_ID
#define LEDG_PIN PIN2_ID

//Define Buzzer port
#define BUZZER_PORT PORTD_ID
//Define Buzzer pin
#define BUZZER_PIN PIN0_ID

//Define Button port
#define BUTTON_PORT PORTD_ID
//Define Button pin
#define BUTTON_PIN PIN1_ID


//Define values for motor
#define STOP 	19
#define MAX		40


#endif /* MAIN_H_ */
