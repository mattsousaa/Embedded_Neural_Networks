/*
 * main.c
 *
 *  Created on: Set 19, 2020
 *      Author: Mateus Sousa
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include "main.h"
#include "simple_neural_networks.h"

#define NUM_OF_INPUTS 	3

UART_HandleTypeDef huart3;

void SystemClock_Config(void);
void UART3_Init(void);

double temperature[5] = {12, 23, 50, -10, 16};
double humidity[5] =    {60, 67, 50, 65, 63};
double air_quality[5] = {60, 47, 167, 187, 94};

double weight[3] = {-2, 2, 1};

void printmsg(char *format, ...){

	char str[80];

	/*Extract the argument list using VA apis */
	va_list args;
	va_start(args, format);
	vsprintf(str, format, args);
	HAL_UART_Transmit(&huart3, (uint8_t*) str, strlen(str), HAL_MAX_DELAY);
	va_end(args);

}

int main(void){

	double training_eg1[3] = {temperature[0], humidity[0], air_quality[0]};

	HAL_Init();
	SystemClock_Config();
	UART3_Init();

	printmsg("Prediction from first training example is: %f\r\n ", multiple_inputs_single_output_nn(training_eg1, weight, NUM_OF_INPUTS));

	while(1);

}

void SystemClock_Config(void){

}

void UART3_Init(void){

	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;

	if(HAL_UART_Init(&huart3) != HAL_OK){
		Error_Handler();
	}

}

void Error_Handler(void){
  while(1);
}

