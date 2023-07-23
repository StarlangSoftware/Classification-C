//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_STRATIFIEDKFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_STRATIFIEDKFOLDRUNSEPARATETEST_H

#include "Experiment.h"
#include "../Performance/ExperimentPerformance.h"

Experiment_performance_ptr execute_stratified_k_fold_run_separate_test(const Experiment* experiment, int K);

#endif //CLASSIFICATION_STRATIFIEDKFOLDRUNSEPARATETEST_H
