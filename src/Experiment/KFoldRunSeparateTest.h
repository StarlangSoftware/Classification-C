//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_KFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_KFOLDRUNSEPARATETEST_H

#include "Experiment.h"
#include "../Performance/ExperimentPerformance.h"

Experiment_performance_ptr execute_k_fold_run_separate_test(const Experiment* experiment, int K);

#endif //CLASSIFICATION_KFOLDRUNSEPARATETEST_H
