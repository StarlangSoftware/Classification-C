//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <Memory/Memory.h>
#include "KnnParameter.h"
#include "../DistanceMetric/EuclidianDistance.h"

/**
 * Parameters of the K-nearest neighbor classifier.
 *
 * @param seed           Seed is used for random number generation.
 * @param k              Parameter of the K-nearest neighbor algorithm.
 * @param distance_function Used to calculate the distance between two instances.
 */
Knn_parameter_ptr
create_knn_parameter(int seed, int k, double (*distance_function)(const Instance *, const Instance *, const void *)) {
    Knn_parameter_ptr result = malloc_(sizeof(Knn_parameter));
    result->seed = seed;
    result->k = k;
    result->distance_function = distance_function;
    return result;
}

/**
 * Parameters of the K-nearest neighbor classifier.
 *
 * @param seed           Seed is used for random number generation.
 * @param k              Parameter of the K-nearest neighbor algorithm.
 */
Knn_parameter_ptr create_knn_parameter2(int seed, int k) {
    Knn_parameter_ptr result = malloc_(sizeof(Knn_parameter));
    result->seed = seed;
    result->k = k;
    result->distance_function = euclidian_distance;
    return result;
}

void free_knn_parameter(Knn_parameter_ptr knn_parameter) {
    free_(knn_parameter);
}
