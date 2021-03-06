/*
 * simple_neural_networks.c
 *
 *  Created on: Sep 19, 2020
 *      Author: Mateus Sousa
 */

#include "simple_neural_networks.h"

double single_in_single_out_nn(double  input, double weight){
   	return (input * weight);
}


double weighted_sum(double *input, double *weight, uint32_t input_len){
	double output;

	for(int i = 0; i < input_len; i++){
	  output += input[i] * weight[i];
	}

 return output;
}

double multiple_inputs_single_output_nn(double *input, double *weight, uint32_t input_len){

	double predicted_value;

	predicted_value =  weighted_sum(input, weight, input_len);

	return predicted_value;
}

