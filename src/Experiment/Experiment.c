//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#include <stdlib.h>
#include "Experiment.h"

Experiment_ptr create_experiment(Classifier_ptr classifier, void *parameter, Data_set_ptr data_set, int seed) {
    Experiment_ptr result = malloc(sizeof(Experiment));
    result->classifier = classifier;
    result->parameter = parameter;
    result->data_set = data_set;
    result->seed = seed;
    return result;
}

void free_experiment(Experiment_ptr experiment) {
    free(experiment);
}
