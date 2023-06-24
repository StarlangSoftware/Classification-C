//
// Created by Olcay Taner YILDIZ on 22.06.2023.
//

#include "../InstanceList/InstanceList.h"

#ifndef CLASSIFICATION_KMEANSMODEL_H
#define CLASSIFICATION_KMEANSMODEL_H

struct k_means_model{
    Discrete_distribution_ptr prior_distribution;
    Instance_list_ptr class_means;
    double (*distance_metric)(const Instance* instance1, const Instance* instance2, const void* parameter);
};

typedef struct k_means_model K_means_model;

typedef K_means_model *K_means_model_ptr;

K_means_model_ptr create_k_means_model(Discrete_distribution_ptr prior_distribution,
                                       Instance_list_ptr class_means,
                                       double (*distance_metric)(const Instance* instance1, const Instance* instance2, const void* parameter));

K_means_model_ptr create_k_means_model2(const char* file_name);

void free_k_means_model(K_means_model_ptr k_means_model);

char* predict_k_means(const void* model, const Instance* instance);

double calculate_metric_k_means(const K_means_model* k_means_model, const Instance* instance, const char* C_i);

#endif //CLASSIFICATION_KMEANSMODEL_H
