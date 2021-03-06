/*
 * simple_neural_networks.h
 *
 *  Created on: Sep 19, 2020
 *      Author: Mateus Sousa
 */

#ifndef INC_SIMPLE_NEURAL_NETWORKS_H_
#define INC_SIMPLE_NEURAL_NETWORKS_H_

#include <stdint.h>

double single_in_single_out_nn(double  input, double weight);
double weighted_sum(double * input, double * weight, uint32_t input_len);
double multiple_inputs_single_output_nn(double * input, double *weight, uint32_t input_len);

void single_in_multiple_out_nn(double input_scalar,
							   double *weight_vector,
							   double *out_vector,
							   double vector_len);

void multiple_in_multiple_out_nn(double *input_vector,
								 uint32_t input_len,
								 double *output_vector,
								 uint32_t output_len,
								 double weights_matrix[output_len][input_len]);

void hidden_layer_nn(double *input_vector,
			   	     uint32_t input_len,
					 uint32_t hidden_len,
					 double in_to_hid_weights[hidden_len][input_len],
					 uint32_t output_len,
					 double hid_to_out_weights[output_len][hidden_len],
					 double *output_vector);

double find_error_simple(double yhat, double y);
double find_error(double input, double weight, double expected_value);

#endif /* INC_SIMPLE_NEURAL_NETWORKS_H_ */
