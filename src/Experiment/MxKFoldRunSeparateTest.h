//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#ifndef CLASSIFICATION_MXKFOLDRUNSEPARATETEST_H
#define CLASSIFICATION_MXKFOLDRUNSEPARATETEST_H

#include "../Performance/ExperimentPerformance.h"
#include "Experiment.h"

Experiment_performance_ptr execute_m_x_k_fold_run_separate_test(const Experiment* experiment, int M, int K);

#endif //CLASSIFICATION_MXKFOLDRUNSEPARATETEST_H
