//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_DEEPNETWORKPARAMETER_H
#define CLASSIFICATION_DEEPNETWORKPARAMETER_H

#include <ArrayList.h>
#include "ActivationFunction.h"

struct deep_network_parameter{
    int seed;
    double learning_rate;
    double eta_decrease;
    double cross_validation_ratio;
    int epoch;
    Array_list_ptr hidden_layers;
    Activation_function activation_function;
};

typedef struct deep_network_parameter Deep_network_parameter;

typedef Deep_network_parameter *Deep_network_parameter_ptr;

Deep_network_parameter_ptr create_deep_network_parameter(int seed,
                                                         double learning_rate,
                                                         double eta_decrease,
                                                         double cross_validation_ratio,
                                                         int epoch,
                                                         Array_list_ptr hidden_layers,
                                                         Activation_function activation_function);

void free_deep_network_parameter(Deep_network_parameter_ptr deep_network_parameter);

int layer_size(Deep_network_parameter_ptr deep_network_parameter);

int get_hidden_nodes(Deep_network_parameter_ptr deep_network_parameter, int layer_index);

#endif //CLASSIFICATION_DEEPNETWORKPARAMETER_H
