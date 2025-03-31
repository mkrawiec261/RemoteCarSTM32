/*
 * joystickinit.h
 *
 *  Created on: Nov 10, 2024
 *      Author: Tymoteusz Krasnowski
 *      		Marcin Krawiec
 *
 * @brief Nagłówek zawierający deklaracje i definicje do obsługi joysticka.
 *
 * Ten plik definiuje strukturę Joystick, stałe oraz prototypy funkcji
 * odpowiedzialnych za inicjalizację i przetwarzanie danych joysticka.
 */
/*
#ifndef SRC_JOYSTICKINIT_H_
#define SRC_JOYSTICKINIT_H_
//#include "stm32f3xx_hal_msp.c"
#include <stdio.h>
#include <string.h>

extern ADC_HandleTypeDef hadc1;	  // Obsługa ADC dla joysticka
extern TIM_HandleTypeDef htim2;

#define ADC_MAX 4096       		 // Maksymalna wartość ADC (12-bitowa rozdzielczość)
#define SCALE_FACTOR 4.095   	 // Skalowanie ADC do zakresu 0-1000
#define BUFFER_SIZE 5			 // Liczba próbek w buforze

typedef struct Joystick{		 //Struktura przechowująca dane joysticka

	volatile uint16_t parameter[2]; //volatile to bylo ze tylko dma moze to zmieniac -  uzytkownikowi nie pozwili na zmiane
	uint32_t convertedparameter[2];

}Joystick;

void joystick_run(Joystick *joystick);
void joystick_printconv(Joystick *joystick);
void joystick_conv(Joystick *joystick);


#endif /* SRC_JOYSTICKINIT_H_ */

