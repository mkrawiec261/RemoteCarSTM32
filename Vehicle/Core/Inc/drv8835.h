/*
 * drv8835.h
 *
 *  Created on: Nov 6, 2024
 *      Author: Marcin Krawiec
 *      Plik konfiguracyjny drivera PWM do silnika DC 5V.
 *
 *      Ten plik zawiera deklaracje funkcji oraz typów wykorzystywanych do
 *      sterowania mostkiem H DRV8835, umożliwiającym kontrolę dwóch silników
 *      DC przy użyciu sygnałów PWM oraz sygnałów kierunku obrotów.
 */

#ifndef INC_DRV8835_H_
#define INC_DRV8835_H_

#include <stdint.h>

//---------------------------------------------------------------------------------
typedef enum
{
	In_In_Mode = 0,
	Phase_Enable_Mode = 1
}DRV8835_Mode;

//---------------------------------------------------------------------------------
typedef enum
{
	CWA = 0,
	CCWA = 1
}DRV8835_DirectionA;
//---------------------------------------------------------------------------------

typedef enum
{
	CWB = 0,
	CCWB = 1
}DRV8835_DirectionB;
//---------------------------------------------------------------------------------


void drv8835_init();
void drv8835_mode_control(DRV8835_Mode);
void drv8835_set_motorA_direction(DRV8835_DirectionA);
void drv8835_set_motorB_direction(DRV8835_DirectionB);
void drv8835_set_motorA_speed(uint16_t speedA);
void drv8835_set_motorB_speed(uint16_t speedB);
uint16_t drv8835_limit_motor_speed(int16_t speed);

#endif /* INC_DRV8835_H_ */
