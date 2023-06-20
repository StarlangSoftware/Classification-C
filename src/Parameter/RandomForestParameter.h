//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_RANDOMFORESTPARAMETER_H
#define CLASSIFICATION_RANDOMFORESTPARAMETER_H

struct random_forest_parameter{
    int ensemble_size;
    int seed;
    int attribute_subset_size;
};

typedef struct random_forest_parameter Random_forest_parameter;

typedef Random_forest_parameter *Random_forest_parameter_ptr;

Random_forest_parameter_ptr create_random_forest_parameter(int seed,
                                                           int ensemble_size,
                                                           int attribute_subset_size);

void free_random_forest_parameter(Random_forest_parameter_ptr random_forest_parameter);

#endif //CLASSIFICATION_RANDOMFORESTPARAMETER_H
