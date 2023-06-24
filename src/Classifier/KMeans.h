//
// Created by Olcay Taner YILDIZ on 23.06.2023.
//

#ifndef CLASSIFICATION_KMEANS_H
#define CLASSIFICATION_KMEANS_H

#include "Classifier.h"

Classifier_ptr train_k_means(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_k_means(const char* file_name);

void free_k_means(Classifier_ptr k_means);

#endif //CLASSIFICATION_KMEANS_H
