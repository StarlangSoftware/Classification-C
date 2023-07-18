//
// Created by Olcay Taner YILDIZ on 18.07.2023.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRON_H
#define CLASSIFICATION_LINEARPERCEPTRON_H

#include "Classifier.h"
#include "../Model/LinearPerceptronModel.h"

Classifier_ptr train_linear_perceptron(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_linear_perceptron(const char* file_name);

Classifier_ptr validation_linear_perceptron(Linear_perceptron_model_ptr linear_perceptron);

void free_linear_perceptron(Classifier_ptr linear_perceptron);

#endif //CLASSIFICATION_LINEARPERCEPTRON_H
