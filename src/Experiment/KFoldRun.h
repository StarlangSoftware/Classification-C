//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_KFOLDRUN_H
#define CLASSIFICATION_KFOLDRUN_H

#include "Experiment.h"
#include "../Performance/ExperimentPerformance.h"

Experiment_performance_ptr execute_k_fold_run(const Experiment* experiment, int K);

#endif //CLASSIFICATION_KFOLDRUN_H
