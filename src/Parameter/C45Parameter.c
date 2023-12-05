//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "C45Parameter.h"

/**
 * Parameters of the C4.5 univariate decision tree classifier.
 *
 * @param seed                 Seed is used for random number generation.
 * @param prune                Boolean value for prune.
 * @param cross_validation_ratio Double value for cross crossValidationRatio ratio.
 */
C45_parameter_ptr create_c45_parameter(int seed,
                                       bool prune,
                                       double cross_validation_ratio) {
    C45_parameter_ptr result = malloc_(sizeof(C45_parameter), "create_c45_parameter");
    result->seed = seed;
    result->prune = prune;
    result->cross_validation_ratio = cross_validation_ratio;
    return result;
}

void free_c45_parameter(C45_parameter_ptr c45_parameter) {
    free_(c45_parameter);
}
