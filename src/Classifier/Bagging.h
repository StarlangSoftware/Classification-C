//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#ifndef CLASSIFICATION_BAGGING_H
#define CLASSIFICATION_BAGGING_H

#include "Classifier.h"
#include "../InstanceList/InstanceList.h"

Classifier_ptr train_bagging(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_bagging(const char* file_name);

void free_bagging(Classifier_ptr bagging);

#endif //CLASSIFICATION_BAGGING_H
