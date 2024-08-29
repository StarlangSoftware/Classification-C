//
// Created by Olcay Taner YILDIZ on 17.07.2023.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRONMODEL_H
#define CLASSIFICATION_LINEARPERCEPTRONMODEL_H

#include <Matrix.h>
#include "../../InstanceList/InstanceList.h"
#include "../../Parameter/LinearPerceptronParameter.h"
#include "NeuralNetworkModel.h"
#include "../Model.h"

struct linear_perceptron_model{
    Neural_network_model_ptr model;
    Matrix_ptr W;
};

typedef struct linear_perceptron_model Linear_perceptron_model;

typedef Linear_perceptron_model *Linear_perceptron_model_ptr;

Linear_perceptron_model_ptr create_linear_perceptron_model(Instance_list_ptr train_set,
                                                           Instance_list_ptr validation_set,
                                                           Linear_perceptron_parameter_ptr parameter);


Linear_perceptron_model_ptr create_linear_perceptron_model2(const char* file_name);

void free_linear_perceptron_model(Linear_perceptron_model_ptr linear_perceptron);

char* predict_linear_perceptron(const void *model, const Instance *instance);

Hash_map_ptr predict_probability_linear_perceptron(const void *model, const Instance* instance);

void calculate_output_linear_perceptron(const Linear_perceptron_model* linear_perceptron);

Model_ptr train_linear_perceptron(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_linear_perceptron(const char* file_name);

Model_ptr validation_linear_perceptron(Linear_perceptron_model_ptr linear_perceptron);

void free_linear_perceptron(Model_ptr linear_perceptron);

#endif //CLASSIFICATION_LINEARPERCEPTRONMODEL_H
