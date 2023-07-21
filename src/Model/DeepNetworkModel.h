//
// Created by Olcay Taner YILDIZ on 21.07.2023.
//

#ifndef CLASSIFICATION_DEEPNETWORKMODEL_H
#define CLASSIFICATION_DEEPNETWORKMODEL_H

#include "../Parameter/ActivationFunction.h"
#include "NeuralNetworkModel.h"
#include "../Parameter/DeepNetworkParameter.h"

struct deep_network_model{
    Neural_network_model_ptr model;
    Array_list_ptr weights;
    int hidden_layer_size;
    Activation_function activation_function;
};

typedef struct deep_network_model Deep_network_model;

typedef Deep_network_model *Deep_network_model_ptr;

Deep_network_model_ptr create_deep_network_model(Instance_list_ptr train_set,
                                                 Instance_list_ptr validation_set,
                                                 Deep_network_parameter_ptr parameter);

Deep_network_model_ptr create_deep_network_model2(const char* file_name);

void free_deep_network_model(Deep_network_model_ptr deep_network);

void allocate_deep_network_weights(Deep_network_model_ptr deep_network, Deep_network_parameter_ptr deep_network_parameter);

Array_list_ptr set_best_weights(Deep_network_model_ptr deep_network);

char* predict_deep_network(const void *model, const Instance *instance);

Hash_map_ptr predict_probability_deep_network(const void *model, const Instance* instance);

void calculate_output_deep_network(const Deep_network_model *deep_network);

#endif //CLASSIFICATION_DEEPNETWORKMODEL_H
