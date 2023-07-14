//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#ifndef CLASSIFICATION_RANDOMFOREST_H
#define CLASSIFICATION_RANDOMFOREST_H

#include "../InstanceList/InstanceList.h"
#include "Classifier.h"

Classifier_ptr train_random_forest(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_random_forest(const char* file_name);

void free_random_forest(Classifier_ptr random_forest);

#endif //CLASSIFICATION_RANDOMFOREST_H
