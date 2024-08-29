//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#ifndef CLASSIFICATION_NEURALNETWORKMODEL_H
#define CLASSIFICATION_NEURALNETWORKMODEL_H

#include <ArrayList.h>
#include <Vector.h>
#include "../../InstanceList/InstanceList.h"
#include "../../Parameter/ActivationFunction.h"

struct neural_network_model{
    int K;
    int d;
    Vector_ptr x;
    Vector_ptr y;
    Vector_ptr r;
    Array_list_ptr class_labels;
};

typedef struct neural_network_model Neural_network_model;

typedef Neural_network_model *Neural_network_model_ptr;

Neural_network_model_ptr create_neural_network_model(const Instance_list * train_set);

Neural_network_model_ptr create_neural_network_model2(FILE* input_file);

void free_neural_network_model(Neural_network_model_ptr neural_network);

void free_temporary_input_output_vectors(Neural_network_model_ptr neural_network);

Vector_ptr normalize_output(const Vector *o);

Vector_ptr create_input_vector(const Instance *instance);

Vector_ptr
calculate_r_minus_y(Neural_network_model_ptr neural_network, const Instance *instance, const Vector *input,
                    const Matrix *weights);

Matrix_ptr allocate_layer_weights(int row, int column, int seed);

Vector_ptr calculate_hidden(const Vector *input, const Matrix *weights, Activation_function activation_function);

Vector_ptr calculate_one_minus_hidden(const Vector *hidden);

void calculate_forward_single_hidden_layer(Neural_network_model_ptr neural_network, const Matrix *W, const Matrix *V, Activation_function activation_function);

char* predict_neural_network(Neural_network_model_ptr neural_network_model, const Instance *instance, const void* meta_model, void calculate_output(const void* model));

Hash_map_ptr predict_probability_neural_network(Neural_network_model_ptr neural_network_model, const Instance* instance, const void* meta_model, void calculate_output(const void* model));

Activation_function get_activation_function(FILE* input_file);

#endif //CLASSIFICATION_NEURALNETWORKMODEL_H
