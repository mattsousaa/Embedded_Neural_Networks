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

#define SAD   0.9

#define TEMPERATURE_PREDICTION_IDX	0
#define HUMIDITY_PREDICTION_IDX		1
#define AIR_QUALITY_PREDICTION_IDX  2

#define OUT_LEN						3

double predicted_results[3];

double weights[3] = {-20, 95, 201.0};	//temp   hum   air_q

UART_HandleTypeDef huart3;

void SystemClock_Config(void);
void UART3_Init(void);

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

	HAL_Init();
	SystemClock_Config();
	UART3_Init();

	single_in_multiple_out_nn(SAD, weights, predicted_results, OUT_LEN);

	printmsg("Predicted temperature is: %f\r\n", predicted_results[TEMPERATURE_PREDICTION_IDX]);
	printmsg("Predicted humidity is: %f\r\n", predicted_results[HUMIDITY_PREDICTION_IDX]);
	printmsg("Predicted air quality is: %f\r\n", predicted_results[AIR_QUALITY_PREDICTION_IDX]);

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

