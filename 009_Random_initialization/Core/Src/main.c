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

UART_HandleTypeDef huart3;

#define NUM_OF_FEATURES   	2  // n values
#define NUM_OF_EXAMPLES		3  // m values
#define NUM_OF_HID_NODES	3
#define NUM_OF_OUT_NODES	1

/*Hours of workout data*/
double x1[NUM_OF_EXAMPLES] = {2, 5, 1};
double _x1[NUM_OF_EXAMPLES]; // normalized

/*Hours of rest data*/
double x2[NUM_OF_EXAMPLES] = {8, 5, 8};
double _x2[NUM_OF_EXAMPLES]; // normalized

/*Muscle gain data*/
double y[NUM_OF_EXAMPLES] = {200, 90, 190};
double _y[NUM_OF_EXAMPLES]; // normalized

/*Input layer to hidden layer weight matrix*/
double syn0[NUM_OF_HID_NODES][NUM_OF_FEATURES]; // synapse 0

/*Hidden layer to output layer weight matrix*/
double syn1[NUM_OF_OUT_NODES][NUM_OF_HID_NODES]; // synapse 1

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

	weights_random_initialization(NUM_OF_HID_NODES, NUM_OF_FEATURES, syn0);
	weights_random_initialization(NUM_OF_OUT_NODES, NUM_OF_HID_NODES, syn1);

	/*Synase 0 weights*/
	for (int i = 0; i < NUM_OF_HID_NODES; i++) {
		for (int j = 0; j < NUM_OF_FEATURES; j++) {

			printmsg("  %f  ", syn0[i][j]);
		}
		printmsg("\n\r");
		printmsg("\n\r");
	}

	printmsg("\n\r");
	printmsg("\n\r");

	/*Synase 1 weights*/
	for (int i = 0; i < NUM_OF_OUT_NODES; i++) {
		for (int j = 0; j < NUM_OF_HID_NODES; j++) {

			printmsg("  %f  ", syn1[i][j]);
		}
		printmsg("\n\r");
		printmsg("\n\r");
	}

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

