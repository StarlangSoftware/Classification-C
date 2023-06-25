//
// Created by Olcay Taner YILDIZ on 24.06.2023.
//

#ifndef CLASSIFICATION_KNN_MODEL_H
#define CLASSIFICATION_KNN_MODEL_H

#include "../InstanceList/InstanceList.h"

struct knn_model{
    Instance_list_ptr data;
    int k;
    double (*distance_metric)(const Instance* instance1, const Instance* instance2, const void* parameter);
};

typedef struct knn_model Knn_model;

typedef Knn_model *Knn_model_ptr;

Knn_model_ptr create_knn_model(Instance_list_ptr data, int k, double (*distance_metric)(const Instance* instance1, const Instance* instance2, const void* parameter));

Knn_model_ptr create_knn_model2(const char* file_name);

void free_knn_model(Knn_model_ptr knn_model);

Instance_list_ptr nearest_neighbors(const Knn_model* knn_model, const Instance* instance);

char* predict_knn(const void* model, const Instance* instance);

Hash_map_ptr predict_probability_knn(const void* model, const Instance* instance);

#endif //CLASSIFICATION_KNN_MODEL_H
