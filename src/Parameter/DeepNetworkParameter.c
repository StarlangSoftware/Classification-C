//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "DeepNetworkParameter.h"

/**
 * Parameters of the deep network classifier.
 *
 * @param seed                 Seed is used for random number generation.
 * @param learning_rate         Double value for learning rate of the algorithm.
 * @param eta_decrease          Double value for decrease in eta of the algorithm.
 * @param cross_validation_ratio Double value for cross validation ratio of the algorithm.
 * @param epoch                Integer value for epoch number of the algorithm.
 * @param hidden_layers         An integer vector for hidden layers of the algorithm.
 * @param activation_function   Activation function
 */
Deep_network_parameter_ptr
create_deep_network_parameter(int seed,
                              double learning_rate,
                              double eta_decrease,
                              double cross_validation_ratio,
                              int epoch,
                              Array_list_ptr hidden_layers,
                              Activation_function activation_function) {
    Deep_network_parameter_ptr result = malloc_(sizeof(Deep_network_parameter), "create_deep_network_parameter");
    result->seed = seed;
    result->learning_rate = learning_rate;
    result->eta_decrease = eta_decrease;
    result->cross_validation_ratio = cross_validation_ratio;
    result->epoch = epoch;
    result->hidden_layers = hidden_layers;
    result->activation_function = activation_function;
    return result;
}

void free_deep_network_parameter(Deep_network_parameter_ptr deep_network_parameter) {
    free_array_list(deep_network_parameter->hidden_layers, free_);
    free_(deep_network_parameter);
}

/**
 * The layerSize method returns the size of the hiddenLayers ArrayList.
 *
 * @return The size of the hiddenLayers ArrayList.
 */
int layer_size(Deep_network_parameter_ptr deep_network_parameter) {
    return deep_network_parameter->hidden_layers->size;
}

/**
 * The getHiddenNodes method takes a layer index as an input and returns the element at the given index of hiddenLayers
 * vector.
 *
 * @param layerIndex Index of the layer.
 * @return The element at the layerIndex of hiddenLayers vector.
 */
int get_hidden_nodes(Deep_network_parameter_ptr deep_network_parameter, int layer_index) {
    return *(int*)array_list_get(deep_network_parameter->hidden_layers, layer_index);
}
