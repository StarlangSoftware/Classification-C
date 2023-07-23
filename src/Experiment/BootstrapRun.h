//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_BOOTSTRAPRUN_H
#define CLASSIFICATION_BOOTSTRAPRUN_H

#include "Experiment.h"
#include "../Performance/ExperimentPerformance.h"

Experiment_performance_ptr execute_bootstrap(const Experiment* experiment, int number_of_bootstraps);

#endif //CLASSIFICATION_BOOTSTRAPRUN_H
