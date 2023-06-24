//
// Created by Olcay Taner YILDIZ on 21.06.2023.
//

#ifndef CLASSIFICATION_RANDOMCLASSIFIER_H
#define CLASSIFICATION_RANDOMCLASSIFIER_H

#include "../InstanceList/InstanceList.h"
#include "Classifier.h"
#include "../Performance/DetailedClassificationPerformance.h"

Classifier_ptr train_random(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_random(const char* file_name);

void free_random(Classifier_ptr random);

#endif //CLASSIFICATION_RANDOMCLASSIFIER_H
