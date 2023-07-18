//
// Created by Olcay Taner YILDIZ on 17.07.2023.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRONMODEL_H
#define CLASSIFICATION_LINEARPERCEPTRONMODEL_H

#include <Matrix.h>
#include "../InstanceList/InstanceList.h"
#include "../Parameter/LinearPerceptronParameter.h"

struct linear_perceptron_model{
    Matrix_ptr W;
    int K;
    int d;
    Vector_ptr x;
    Vector_ptr y;
    Vector_ptr r;
    Array_list_ptr class_labels;
};

typedef struct linear_perceptron_model Linear_perceptron_model;

typedef Linear_perceptron_model *Linear_perceptron_model_ptr;

Linear_perceptron_model_ptr create_linear_perceptron_model(Instance_list_ptr train_set,
                                                           Instance_list_ptr validation_set,
                                                           Linear_perceptron_parameter_ptr parameter);


Linear_perceptron_model_ptr create_linear_perceptron_model2(const char* file_name);

void free_linear_perceptron_model(Linear_perceptron_model_ptr linear_perceptron);

Matrix_ptr allocate_layer_weights(int row, int column, int seed);

Vector_ptr create_input_vector(const Instance *instance);

Vector_ptr calculate_r_minus_y(Linear_perceptron_model_ptr linear_perceptron, const Instance* instance, const Vector *input, const Matrix* weights);

Vector_ptr normalize_output(const Vector *o);

char* predict_linear_perceptron(const void *model, const Instance *instance);

Hash_map_ptr predict_probability_linear_perceptron(const void *model, const Instance* instance);

void calculate_output_linear_perceptron(Linear_perceptron_model_ptr linear_perceptron);

#endif //CLASSIFICATION_LINEARPERCEPTRONMODEL_H
