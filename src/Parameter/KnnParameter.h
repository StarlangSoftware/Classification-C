//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_KNNPARAMETER_H
#define CLASSIFICATION_KNNPARAMETER_H

#include "../Instance/Instance.h"

struct knn_parameter{
    int k;
    int seed;
    double (*distance_function)(const Instance*, const Instance*, const void*);
};

typedef struct knn_parameter Knn_parameter;

typedef Knn_parameter *Knn_parameter_ptr;

Knn_parameter_ptr create_knn_parameter(int seed, int k, double (*distance_function)(const Instance*, const Instance*, const void*));

Knn_parameter_ptr create_knn_parameter2(int seed, int k);

void free_knn_parameter(Knn_parameter_ptr knn_parameter);

#endif //CLASSIFICATION_KNNPARAMETER_H
