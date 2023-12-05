//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "MultiLayerPerceptronParameter.h"

/**
 * Parameters of the multi layer perceptron algorithm.
 *
 * @param seed                 Seed is used for random number generation.
 * @param learning_rate         Double value for learning rate of the algorithm.
 * @param eta_decrease          Double value for decrease in eta of the algorithm.
 * @param cross_validation_ratio Double value for cross validation ratio of the algorithm.
 * @param epoch                Integer value for epoch number of the algorithm.
 * @param hidden_nodes          Integer value for the number of hidden nodes.
 * @param activation_function   Activation function
 */
Multi_layer_perceptron_parameter_ptr
create_multi_layer_perceptron_parameter_ptr(int seed,
                                            double learning_rate,
                                            double eta_decrease,
                                            double cross_validation_ratio,
                                            int epoch,
                                            int hidden_nodes,
                                            Activation_function activation_function) {
    Multi_layer_perceptron_parameter_ptr result = malloc_(sizeof(Multi_layer_perceptron_parameter), "create_multi_layer_perceptron_parameter_ptr");
    result->seed = seed;
    result->learning_rate = learning_rate;
    result->eta_decrease = eta_decrease;
    result->cross_validation_ratio = cross_validation_ratio;
    result->epoch = epoch;
    result->hidden_nodes = hidden_nodes;
    result->activation_function = activation_function;
    return result;
}

void
free_multi_layer_perceptron_parameter_ptr(Multi_layer_perceptron_parameter_ptr multi_layer_perceptron_parameter) {
    free_(multi_layer_perceptron_parameter);
}
