//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#ifndef CLASSIFICATION_MULTILAYERPERCEPTRON_H
#define CLASSIFICATION_MULTILAYERPERCEPTRON_H

#include "Classifier.h"
#include "../Model/MultiLayerPerceptronModel.h"

Classifier_ptr train_multi_layer_perceptron(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_multi_layer_perceptron(const char* file_name);

Classifier_ptr validation_multi_layer_perceptron(Multi_layer_perceptron_model_ptr multi_layer_perceptron);

void free_multi_layer_perceptron(Classifier_ptr multi_layer_perceptron);

#endif //CLASSIFICATION_MULTILAYERPERCEPTRON_H
