//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_EXPERIMENT_H
#define CLASSIFICATION_EXPERIMENT_H

#include "../Classifier/Classifier.h"
#include "../DataSet/DataSet.h"

struct experiment{
    Classifier_ptr classifier;
    void* parameter;
    Data_set_ptr data_set;
    int seed;
};

typedef struct experiment Experiment;

typedef Experiment *Experiment_ptr;

Experiment_ptr create_experiment(Classifier_ptr classifier, void* parameter, Data_set_ptr data_set, int seed);

void free_experiment(Experiment_ptr experiment);

#endif //CLASSIFICATION_EXPERIMENT_H
