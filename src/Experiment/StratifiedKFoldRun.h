//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_STRATIFIEDKFOLDRUN_H
#define CLASSIFICATION_STRATIFIEDKFOLDRUN_H

#include "../Performance/ExperimentPerformance.h"
#include "Experiment.h"

Experiment_performance_ptr execute_stratified_k_fold_run(const Experiment* experiment, int K);

#endif //CLASSIFICATION_STRATIFIEDKFOLDRUN_H
