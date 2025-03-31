/* USER CODE BEGIN Header */
/**
  ****************************************************************************
  * @file           : dataread.c
  * @brief          : Konwersja danych z uarta na wartosci 16 bitowe + synchronizacja
  ****************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  * *
  ****************************************************************************
   * @author         : [Tymoteusz Krasnowski]
   * @date           : [08.12.2024]
   * @version        : [1.0]
   * @description    : Funkcja zlepiajajaca 2 liczby 8 bitowe w jedna 16-bitowa,
   * zgodnie ze znakiem synchronizacji
  */
/* USER CODE END Header */

#include "stm32f3xx_hal.h"
#include "wifidataconvert.h"
#include "dataread.h"

Dataread dataread;

void convertwifidata(Wifidataconv *wifidataconv) {
    for (uint8_t i = 0; i < 5; i++) {
        if (dataread.rxbuffer[i] == 0xA0 ) {
            switch (i) {
                case 0:
                    wifidataconv->posX = dataread.rxbuffer[1] << 8 | dataread.rxbuffer[2];
                    wifidataconv->posY = dataread.rxbuffer[3] << 8 | dataread.rxbuffer[4];
                    break;
                case 1:
                    wifidataconv->posX = dataread.rxbuffer[2] << 8 | dataread.rxbuffer[3];
                    wifidataconv->posY = dataread.rxbuffer[4] << 8 | dataread.rxbuffer[0];
                    break;
                case 2:
                    wifidataconv->posX = dataread.rxbuffer[3] << 8 | dataread.rxbuffer[4];
                    wifidataconv->posY = dataread.rxbuffer[0] << 8 | dataread.rxbuffer[1];
                    break;
                case 3:
                    wifidataconv->posX = dataread.rxbuffer[4] << 8 | dataread.rxbuffer[0];
                    wifidataconv->posY = dataread.rxbuffer[1] << 8 | dataread.rxbuffer[2];
                    break;
                case 4:
                    wifidataconv->posX = dataread.rxbuffer[0] << 8 | dataread.rxbuffer[1];
                    wifidataconv->posY = dataread.rxbuffer[2] << 8 | dataread.rxbuffer[3];
                    break;
            }

            printf("%d, %d\n", wifidataconv->posX, wifidataconv->posY);
            HAL_Delay(150);
            break;
        }
    }
}


/*** Funkcja sortuje bufor i zwraca jego medianę. Służy do filtrowania szumu w danych ADC */

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
void joystick_conv(Wifidataconv *wifidataconv)
{
    static uint16_t buffer_x[BUFFER_SIZE] = {0}; 	// Bufor dla osi X
    static uint16_t buffer_y[BUFFER_SIZE] = {0};	// Bufor dla osi Y
    static uint8_t buffer_index = 0;				// Indeks cykliczny dla bufora

    // Dodawanie nowych danych do buforów
    buffer_x[buffer_index] = wifidataconv->posX;
    buffer_y[buffer_index] = wifidataconv->posY;
    buffer_index = (buffer_index + 1) % BUFFER_SIZE; // Cykliczny indeks

    // Przetwarzanie danych filtrem medianowym
    wifidataconv->posX = (get_median(buffer_x) * 1000) / 4096; 			// Skalowanie na 0-1000
    wifidataconv->posY = 1000 - ((get_median(buffer_y) * 1000) / 4096);
}

void joystick_printconv(Wifidataconv *wifidataconv)
{
	 printf("%d, %d\n", wifidataconv->posX, wifidataconv->posY);
	 HAL_Delay(50);
}
