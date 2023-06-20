//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_BAGGINGPARAMETER_H
#define CLASSIFICATION_BAGGINGPARAMETER_H

struct bagging_parameter{
    int ensemble_size;
    int seed;
};

typedef struct bagging_parameter Bagging_parameter;

typedef Bagging_parameter *Bagging_parameter_ptr;

Bagging_parameter_ptr create_bagging_parameter(int seed, int ensemble_size);

void free_bagging_parameter(Bagging_parameter_ptr bagging_parameter);

#endif //CLASSIFICATION_BAGGINGPARAMETER_H
