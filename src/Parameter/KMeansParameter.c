//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "KMeansParameter.h"
#include "../DistanceMetric/EuclidianDistance.h"

/**
 * * Parameters of the Rocchio classifier.
 *
 * @param seed           Seed is used for random number generation.
 * @param distanceMetric distance metric used to calculate the distance between two instances.
 */
K_means_parameter_ptr
create_k_means_parameter(int seed, double (*distance_function)(const Instance *, const Instance *, const void *)) {
    K_means_parameter_ptr result = malloc_(sizeof(K_means_parameter), "create_k_means_parameter");
    result->seed = seed;
    result->distance_function = distance_function;
    return result;
}

/**
 * Parameters of the Rocchio classifier.
 *
 * @param seed Seed is used for random number generation.
 */
K_means_parameter_ptr create_k_means_parameter2(int seed) {
    K_means_parameter_ptr result = malloc_(sizeof(K_means_parameter), "create_k_means_parameter2");
    result->seed = seed;
    result->distance_function = euclidian_distance;
    return result;
}

void free_k_mean_parameter(K_means_parameter_ptr k_means_parameter) {
    free_(k_means_parameter);
}
