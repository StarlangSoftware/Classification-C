//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_STRATIFIEDMXKFOLDRUN_H
#define CLASSIFICATION_STRATIFIEDMXKFOLDRUN_H

#include "../Performance/ExperimentPerformance.h"
#include "Experiment.h"

Experiment_performance_ptr execute_stratified_m_x_k_fold_run(const Experiment* experiment, int M, int K);

#endif //CLASSIFICATION_STRATIFIEDMXKFOLDRUN_H
