/*
 * it.c
 *
 *  Created on: Set 19, 2020
 *      Author: Mateus Sousa
 */

#include "main.h"
#include "stm32f7xx_it.h"

void SysTick_Handler(void){
	HAL_IncTick();
}
