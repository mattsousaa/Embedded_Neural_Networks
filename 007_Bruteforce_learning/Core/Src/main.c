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
#include <math.h>
#include "main.h"
#include "simple_neural_networks.h"

double weight = 0.5;
double input = 0.5;
double expected_value = 0.8;
double step_amount = 0.001;

UART_HandleTypeDef huart3;

void SystemClock_Config(void);
void UART3_Init(void);
void brute_force_learning(double input,
						  double weight,
						  double expected_value,
						  double step_amount,	// epoch numbers
						  uint32_t itr);

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

	brute_force_learning(input, weight, expected_value, step_amount, 1500);

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

void brute_force_learning(double input,
						  double weight,
						  double expected_value, /* amount the we increase the weight by (based on the difference between the expected value and predicted value
						  	  	  	  	  	  	 we would decide whether we want to increase or reduce the weight by this variable)*/
						  double step_amount,	 // epoch numbers
						  uint32_t itr){
double prediction, error;
double up_prediction, down_prediction, up_error, down_error;

	for(int i = 0; i < itr; i++){

		prediction = input * weight;
		error = powf((prediction - expected_value), 2);

		printmsg("Error: %f   Prediction: %f \r\n", error, prediction);

		up_prediction = input * (weight + step_amount);
		up_error      = powf((up_prediction - expected_value), 2);

		printmsg("Up Error: %f   Up Prediction: %f \r\n", up_error, up_prediction);

		down_prediction = input * (weight - step_amount);
		down_error      = powf((down_prediction - expected_value), 2);

		printmsg("Down Error: %f   Down Prediction: %f \r\n", down_error, down_prediction);

		if(down_error < up_error){
			weight = weight - step_amount;
			printmsg("Weight: %f   \r\n\r\n", weight);
		}

		if(down_error > up_error){
			weight = weight + step_amount;
			printmsg("Weight: %f   \r\n\r\n", weight);
		}
	}
}

