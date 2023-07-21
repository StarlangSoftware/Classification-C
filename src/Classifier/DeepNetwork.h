//
// Created by Olcay Taner YILDIZ on 21.07.2023.
//

#ifndef CLASSIFICATION_DEEPNETWORK_H
#define CLASSIFICATION_DEEPNETWORK_H

#include "Classifier.h"
#include "../Model/DeepNetworkModel.h"

Classifier_ptr train_deep_network(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_deep_network(const char* file_name);

Classifier_ptr validation_deep_network(Deep_network_model_ptr deep_network);

void free_deep_network(Classifier_ptr deep_network);

#endif //CLASSIFICATION_DEEPNETWORK_H
