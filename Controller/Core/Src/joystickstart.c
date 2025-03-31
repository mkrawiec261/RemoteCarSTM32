/**
 * @file joystickinit.c
 * @brief Implementacja funkcji obsługujących joystick.
 *
 * Ten plik zawiera implementację funkcji do obsługi joysticka, w tym inicjalizację,
 * filtrowanie danych z ADC przy użyciu mediany oraz skalowanie wartości do zakresu 0–1000.
 *
 * @author
 *      Marcin Krawiec
 *      Tymoteusz Krasnowski
 * @date
 *      January 17, 2025
 */

/*
//#include <stdio.h>
#include "stm32f3xx_hal.h"
#include "joystickinit.h"


void joystick_run(Joystick *joystick)		//Funkcja uruchamia kalibrację ADC oraz startuje DMA do odczytu danych z joysticka
{
	 HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	 HAL_ADC_Start_DMA(&hadc1, (uint32_t *)joystick->parameter, 2);
}


/*** Funkcja sortuje bufor i zwraca jego medianę. Służy do filtrowania szumu w danych ADC */
/*
uint16_t get_median(uint16_t *buffer)
{
    uint16_t temp[BUFFER_SIZE];
    memcpy(temp, buffer, sizeof(temp)); // Skopiuj dane, aby nie zmieniać bufora


    // Sortowanie tablicy (metoda bąbelkowa)
    for (int i = 0; i < BUFFER_SIZE - 1; i++) {
        for (int j = i + 1; j < BUFFER_SIZE; j++) {
            if (temp[i] > temp[j]) {
                uint16_t t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    return temp[BUFFER_SIZE / 2];
}

//Funkcja filtruje dane z joysticka za pomocą mediany, a następnie skaluje je do zakresu 0–1000
void joystick_conv(Joystick *joystick)
{
    static uint16_t buffer_x[BUFFER_SIZE] = {0}; 	// Bufor dla osi X
    static uint16_t buffer_y[BUFFER_SIZE] = {0};	// Bufor dla osi Y
    static uint8_t buffer_index = 0;				// Indeks cykliczny dla bufora

    // Dodawanie nowych danych do buforów
    buffer_x[buffer_index] = joystick->parameter[0];
    buffer_y[buffer_index] = joystick->parameter[1];
    buffer_index = (buffer_index + 1) % BUFFER_SIZE; // Cykliczny indeks

    // Przetwarzanie danych filtrem medianowym
    joystick->convertedparameter[0] = (get_median(buffer_x) * 1000) / 4096; 			// Skalowanie na 0-10000
    joystick->convertedparameter[1] = 1000 - ((get_median(buffer_y) * 1000) / 4096);
}

void joystick_printconv(Joystick *joystick)
{
	printf("X = %u, Y = %u\n", joystick->convertedparameter[0], joystick->convertedparameter[1]);

}

*/
