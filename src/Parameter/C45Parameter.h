//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_C45PARAMETER_H
#define CLASSIFICATION_C45PARAMETER_H

#include <stdbool.h>

struct c45_parameter{
    int seed;
    bool prune;
    double cross_validation_ratio;
};

typedef struct c45_parameter C45_parameter;

typedef C45_parameter *C45_parameter_ptr;

C45_parameter_ptr create_c45_parameter(int seed,
                                       bool prune,
                                       double cross_validation_ratio);

void free_c45_parameter(C45_parameter_ptr c45_parameter);

#endif //CLASSIFICATION_C45PARAMETER_H
