//
// Created by Olcay Taner YILDIZ on 24.06.2023.
//

#include <stdlib.h>
#include "KnnInstance.h"

/**
 * The constructor that sets the instance and distance value.
 *
 * @param instance {@link Instance} input.
 * @param distance Double distance value.
 */
Knn_instance_ptr create_knn_instance(Instance_ptr instance, double distance) {
    Knn_instance_ptr result = malloc(sizeof(Knn_instance));
    result->instance = instance;
    result->distance = distance;
    return result;
}

void free_knn_instance(Knn_instance_ptr knn_instance) {
    free(knn_instance);
}

int compare_knn_instance(const Knn_instance *instance1, const Knn_instance *instance2) {
    if (instance1->distance < instance2->distance){
        return -1;
    } else {
        if (instance1->distance > instance2->distance){
            return 1;
        } else {
            return 0;
        }
    }
}
