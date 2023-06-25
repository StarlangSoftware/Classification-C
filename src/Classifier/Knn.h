//
// Created by Olcay Taner YILDIZ on 25.06.2023.
//

#ifndef CLASSIFICATION_KNN_H
#define CLASSIFICATION_KNN_H

#include "Classifier.h"

Classifier_ptr train_knn(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_knn(const char* file_name);

void free_knn(Classifier_ptr knn);

#endif //CLASSIFICATION_KNN_H
