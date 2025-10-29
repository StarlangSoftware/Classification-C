//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <Memory/Memory.h>
#include "BaggingParameter.h"

/**
 * Parameters of the bagging trees algorithm.
 *
 * @param seed         Seed is used for random number generation.
 * @param ensemble_size The number of trees in the bagged forest.
 */
Bagging_parameter_ptr create_bagging_parameter(int seed, int ensemble_size) {
    Bagging_parameter_ptr result = malloc_(sizeof(Bagging_parameter));
    result->seed = seed;
    result->ensemble_size = ensemble_size;
    return result;
}

void free_bagging_parameter(Bagging_parameter_ptr bagging_parameter) {
    free_(bagging_parameter);
}
