//
// Created by Olcay Taner YILDIZ on 24.06.2023.
//

#ifndef CLASSIFICATION_KNNINSTANCE_H
#define CLASSIFICATION_KNNINSTANCE_H

#include "../../Instance/Instance.h"

struct knn_instance{
    double distance;
    Instance_ptr instance;
};

typedef struct knn_instance Knn_instance;

typedef Knn_instance *Knn_instance_ptr;

Knn_instance_ptr create_knn_instance(Instance_ptr instance, double distance);

void free_knn_instance(Knn_instance_ptr knn_instance);

int compare_knn_instance(const Knn_instance* instance1, const Knn_instance* instance2);

#endif //CLASSIFICATION_KNNINSTANCE_H
