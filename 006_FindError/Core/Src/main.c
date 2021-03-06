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

#define  SAD_PREDICTION_IDX			0
#define  SICK_PREDCITION_IDX   		1
#define  ACTIVE_PREDICTION_IDX		2

#define OUT_LEN		3
#define IN_LEN		3
#define HID_LEN		3

double predicted_output[OUT_LEN];

//******************************** temp hum  air_q
double input_to_hidden_weights[HID_LEN][IN_LEN] ={{-2.0, 9.5, 2.01},    //hid[0]
								  	  	  	  	  {-0.8, 7.2, 6.3 },    //hid[1]
												  {-0.5, 0.45, 0.9}};   //hid[2]

//************************************************** hid[0] hid[1]  hid[2]
double hidden_to_output_weights[OUT_LEN][HID_LEN] = {{-1.0, 1.15, 0.11},    //sad?
	  	  	  	  	  	  	  	  	  	  	  	  	 {-0.18, 0.15, -0.01},  //sick?
													 {0.25, -0.25, -0.1}};  //active?

double input_vector[IN_LEN] = {30.0, 87.0, 110.0};		// temp, hum, air_q

double expected_values[OUT_LEN] = {600, 10,-90};		// y values measured empirically

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

	hidden_layer_nn(input_vector, IN_LEN, HID_LEN, input_to_hidden_weights, OUT_LEN, hidden_to_output_weights, predicted_output);

	printmsg("Sad prediction: %f\r\n", predicted_output[SAD_PREDICTION_IDX]);
	printmsg("Sad error: %f\r\n", find_error_simple(predicted_output[SAD_PREDICTION_IDX], expected_values[SAD_PREDICTION_IDX]));

	printmsg("Sick prediction: %f\r\n", predicted_output[SICK_PREDCITION_IDX]);
	printmsg("Sick error: %f\r\n", find_error_simple(predicted_output[SICK_PREDCITION_IDX], expected_values[SICK_PREDCITION_IDX]));

	printmsg("Active prediction: %f\r\n", predicted_output[ACTIVE_PREDICTION_IDX]);
	printmsg("Active error: %f\r\n", find_error_simple(predicted_output[ACTIVE_PREDICTION_IDX], expected_values[ACTIVE_PREDICTION_IDX]));

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

