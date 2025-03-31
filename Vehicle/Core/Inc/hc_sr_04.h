/*
 * hc_sr_04.h
 *
 *  Created on: Jan 5, 2025
 *      Author: root
 */

#ifndef INC_HC_SR_04_H_
#define INC_HC_SR_04_H_

#include <stdint.h>
#include "stm32f3xx_hal.h"

struct us_sensor_str
{
    TIM_HandleTypeDef *htim_echo;
    TIM_HandleTypeDef *htim_trig;
    uint32_t trig_channel;


    volatile uint32_t distance_cm;  //zmienna przechowujaca odleglosc w cm
    volatile uint8_t led_state;     // Zmienna przechowująca stan LEDa

};

void hc_sr_04_init(struct us_sensor_str *us_sensor, TIM_HandleTypeDef *htim_echo, TIM_HandleTypeDef *htim_trig, uint32_t trig_channel);
uint32_t hc_sr_04_convert_us_to_cm(uint32_t distance_us);


#endif /* INC_HC_SR_04_H_ */




