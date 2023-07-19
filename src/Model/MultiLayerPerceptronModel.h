//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#ifndef CLASSIFICATION_MULTILAYERPERCEPTRONMODEL_H
#define CLASSIFICATION_MULTILAYERPERCEPTRONMODEL_H

#include <Matrix.h>
#include "../Parameter/ActivationFunction.h"
#include "NeuralNetworkModel.h"
#include "../Parameter/MultiLayerPerceptronParameter.h"

struct multi_layer_perceptron_model{
    Neural_network_model_ptr model;
    Activation_function activation_function;
    Matrix_ptr W;
    Matrix_ptr V;
};

typedef struct multi_layer_perceptron_model Multi_layer_perceptron_model;

typedef Multi_layer_perceptron_model *Multi_layer_perceptron_model_ptr;

Multi_layer_perceptron_model_ptr create_multi_layer_perceptron_model(Instance_list_ptr train_set,
                                                           Instance_list_ptr validation_set,
                                                           Multi_layer_perceptron_parameter_ptr parameter);

Multi_layer_perceptron_model_ptr create_multi_layer_perceptron_model2(const char* file_name);

void free_multi_layer_perceptron_model(Multi_layer_perceptron_model_ptr multi_layer_perceptron);

void allocate_weights(Multi_layer_perceptron_model_ptr multi_layer_perceptron, int H, int seed);

char* predict_multi_layer_perceptron(const void *model, const Instance *instance);

Hash_map_ptr predict_probability_multi_layer_perceptron(const void *model, const Instance* instance);

void calculate_output_multi_layer_perceptron(const Multi_layer_perceptron_model* multi_layer_perceptron);

#endif //CLASSIFICATION_MULTILAYERPERCEPTRONMODEL_H
