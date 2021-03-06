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

/*
Train x:
	2 5 1
	8 5 8
	dim =  nx X m (features x examples)
*/

double raw_x[NUM_OF_FEATURES][NUM_OF_EXAMPLES] = {{2,5,1},	// Hours of workout data
												  {8,5,8}}; // Hours of rest data

/*Train y
	200  90   100
	dim  = 1 x m*/

double raw_y[1][NUM_OF_EXAMPLES] = {{200,90,190}}; // muscle gain in g

/*Input layer to hidden layer weight matrix*/
double syn0[NUM_OF_HID_NODES][NUM_OF_FEATURES]; // synapse 0

/*Hidden layer to output layer weight vector*/
double syn1[NUM_OF_HID_NODES]; // synapse 1

double train_x[NUM_OF_FEATURES][NUM_OF_EXAMPLES]; 	// normalized data (hours of workout)
double train_y[1][NUM_OF_EXAMPLES];					// normalized data (muscle gain)

double train_x_eg1[NUM_OF_FEATURES];
double train_y_eg1;

double z1_eg1[NUM_OF_HID_NODES];
double a1_eg1[NUM_OF_HID_NODES];
double z2_eg1;
double yhat_eg1;

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

	normalize_data_2d(NUM_OF_FEATURES, NUM_OF_EXAMPLES, raw_x, train_x);
	normalize_data_2d(1, NUM_OF_EXAMPLES, raw_y, train_y);

	train_x_eg1[0] = train_x[0][0]; // 2 h
	train_x_eg1[1] = train_x[1][0]; // 8 h

	train_y_eg1 = train_y[0][0];	// 200 g

	/*Simple test to prove we have the right data*/
	printmsg("train_x_eg1 is [%f   %f] ", train_x_eg1[0], train_x_eg1[1]);
	printmsg("\n\r");
	printmsg("\n\r");
	printmsg("train_y_eg1 is %f", train_y_eg1);
	printmsg("\n\r");

	/*Initialize syn0 and syn1 weights*/
	weights_random_initialization(NUM_OF_HID_NODES, NUM_OF_FEATURES, syn0);
	weights_random_initialization_1d(syn1, NUM_OF_OUT_NODES);

	/*compute z1*/
	multiple_in_multiple_out_nn(train_x_eg1, NUM_OF_FEATURES, z1_eg1, NUM_OF_HID_NODES, syn0);

	/*compute a1*/
	vector_sigmoid(z1_eg1, a1_eg1, NUM_OF_FEATURES);

	/*compute z2*/
	z2_eg1 = multiple_inputs_single_output_nn(a1_eg1, syn1, NUM_OF_FEATURES);
	printmsg("z2_eg1:  %f \n\r", z2_eg1);

	/*compute yhat*/
	yhat_eg1 = sigmoid(z2_eg1);
	printmsg("yhat_eg1:  %f\n\r", yhat_eg1);

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

