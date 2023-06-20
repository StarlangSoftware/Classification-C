//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H
#define CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H

#include "ActivationFunction.h"

struct multi_layer_perceptron_parameter{
    int seed;
    double learning_rate;
    double eta_decrease;
    double cross_validation_ratio;
    int epoch;
    int hidden_nodes;
    Activation_function activation_function;
};

typedef struct multi_layer_perceptron_parameter Multi_layer_perceptron_parameter;

typedef Multi_layer_perceptron_parameter *Multi_layer_perceptron_parameter_ptr;

Multi_layer_perceptron_parameter_ptr create_multi_layer_perceptron_parameter_ptr(int seed,
                                                         double learning_rate,
                                                         double eta_decrease,
                                                         double cross_validation_ratio,
                                                         int epoch,
                                                         int hidden_nodes,
                                                         Activation_function activation_function);

void free_multi_layer_perceptron_parameter_ptr(Multi_layer_perceptron_parameter_ptr multi_layer_perceptron_parameter);

#endif //CLASSIFICATION_MULTILAYERPERCEPTRONPARAMETER_H
