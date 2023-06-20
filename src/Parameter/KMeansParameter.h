//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_KMEANSPARAMETER_H
#define CLASSIFICATION_KMEANSPARAMETER_H

#include "../Instance/Instance.h"

struct k_means_parameter{
    int seed;
    double (*distance_function)(const Instance*, const Instance*, const void*);
};

typedef struct k_means_parameter K_means_parameter;

typedef K_means_parameter *K_means_parameter_ptr;

K_means_parameter_ptr create_k_means_parameter(int seed, double (*distance_function)(const Instance*, const Instance*, const void*));

K_means_parameter_ptr create_k_means_parameter2(int seed);

void free_k_mean_parameter(K_means_parameter_ptr k_means_parameter);

#endif //CLASSIFICATION_KMEANSPARAMETER_H
