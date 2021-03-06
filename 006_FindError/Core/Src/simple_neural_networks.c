/*
 * simple_neural_networks.c
 *
 *  Created on: Sep 19, 2020
 *      Author: Mateus Sousa
 */

#include "simple_neural_networks.h"
#include <math.h>

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

void elementwise_multiply(double input_scalar, double *weight_vector, double *out_vector, double vector_len){

	for(int i = 0; i < vector_len; i++){
		out_vector[i] = input_scalar * weight_vector[i];
	}
}

void single_in_multiple_out_nn(double input_scalar, double *weight_vector, double *out_vector, double vector_len){
	elementwise_multiply(input_scalar, weight_vector, out_vector, vector_len);
}

void matrix_vector_multiplication(double *input_vector, uint32_t input_len, double *output_vector, uint32_t output_len, double weights_matrix[output_len][input_len]){
	for(int k = 0; k < output_len; k++){
		for(int i = 0; i < input_len; i++){
			output_vector[k] += input_vector[i] * weights_matrix[k][i];
		}
	}
}

void multiple_in_multiple_out_nn(double *input_vector,
								 uint32_t input_len,
								 double *output_vector,
								 uint32_t output_len,
								 double weights_matrix[output_len][input_len]){

	matrix_vector_multiplication(input_vector, input_len, output_vector, output_len, weights_matrix);
}

void hidden_layer_nn(double *input_vector,
			   	     uint32_t input_len,
					 uint32_t hidden_len,
					 double in_to_hid_weights[hidden_len][input_len],
					 uint32_t output_len,
					 double hid_to_out_weights[output_len][hidden_len],
					 double *output_vector){

double hidden_pred_vector[hidden_len];

matrix_vector_multiplication(input_vector, input_len, hidden_pred_vector, output_len, in_to_hid_weights);
matrix_vector_multiplication(hidden_pred_vector, hidden_len, output_vector, output_len, hid_to_out_weights);

}

double find_error_simple(double yhat, double y){

	return powf((yhat - y), 2);
}

double find_error(double input, double weight, double expected_value){
	return powf(((input * weight) - expected_value),2);
}
