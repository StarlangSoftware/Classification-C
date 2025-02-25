//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_EXPERIMENT_H
#define CLASSIFICATION_EXPERIMENT_H

#include "../DataSet/DataSet.h"
#include "../Model/Model.h"

struct experiment{
    Model_ptr model;
    void* parameter;
    Data_set_ptr data_set;
    int seed;
};

typedef struct experiment Experiment;

typedef Experiment *Experiment_ptr;

Experiment_ptr create_experiment(Model_ptr model, void* parameter, Data_set_ptr data_set, int seed);

void free_experiment(Experiment_ptr experiment);

Experiment_ptr feature_selected_experiment(const Experiment *experiment, const Feature_sub_set *feature_sub_set);

#endif //CLASSIFICATION_EXPERIMENT_H
