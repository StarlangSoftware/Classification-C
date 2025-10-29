//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <Memory/Memory.h>
#include "LinearPerceptronParameter.h"

/**
 * Parameters of the linear perceptron algorithm.
 *
 * @param seed                 Seed is used for random number generation.
 * @param learning_rate         Double value for learning rate of the algorithm.
 * @param eta_decrease          Double value for decrease in eta of the algorithm.
 * @param cross_validation_ratio Double value for cross validation ratio of the algorithm.
 * @param epoch                Integer value for epoch number of the algorithm.
 */
Linear_perceptron_parameter_ptr
create_linear_perceptron_parameter(int seed,
                                   double learning_rate,
                                   double eta_decrease,
                                   double cross_validation_ratio,
                                   int epoch) {
    Linear_perceptron_parameter_ptr result = malloc_(sizeof(Linear_perceptron_parameter));
    result->seed = seed;
    result->learning_rate = learning_rate;
    result->eta_decrease = eta_decrease;
    result->cross_validation_ratio = cross_validation_ratio;
    result->epoch = epoch;
    return result;
}

void free_linear_perceptron_parameter(Linear_perceptron_parameter_ptr linear_perceptron_parameter) {
    free_(linear_perceptron_parameter);
}
