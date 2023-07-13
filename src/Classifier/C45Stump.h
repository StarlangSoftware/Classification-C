//
// Created by Olcay Taner YILDIZ on 10.07.2023.
//

#ifndef CLASSIFICATION_C45STUMP_H
#define CLASSIFICATION_C45STUMP_H

#include "Classifier.h"

Classifier_ptr train_c45_stump(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_c45_stump(const char* file_name);

void free_c45_stump(Classifier_ptr c45_stump);

#endif //CLASSIFICATION_C45STUMP_H
