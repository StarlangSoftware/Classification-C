//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <stdlib.h>
#include "RandomForestParameter.h"

/**
 * Parameters of the random forest classifier.
 *
 * @param seed                Seed is used for random number generation.
 * @param ensemble_size        The number of trees in the bagged forest.
 * @param attribute_subset_size Integer value for the size of attribute subset.
 */
Random_forest_parameter_ptr create_random_forest_parameter(int seed,
                                                           int ensemble_size,
                                                           int attribute_subset_size) {
    Random_forest_parameter_ptr result = malloc(sizeof(Random_forest_parameter));
    result->seed = seed;
    result->ensemble_size = ensemble_size;
    result->attribute_subset_size = attribute_subset_size;
    return result;
}

void free_random_forest_parameter(Random_forest_parameter_ptr random_forest_parameter) {
    free(random_forest_parameter);
}
