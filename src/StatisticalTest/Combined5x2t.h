//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#ifndef CLASSIFICATION_COMBINED5X2T_H
#define CLASSIFICATION_COMBINED5X2T_H

#include "../Performance/ExperimentPerformance.h"
#include "StatisticalTestResult.h"

double test_statistic_combined_5x2t(const Experiment_performance* classifier1, const Experiment_performance* classifier2);

Statistical_test_result_ptr compare_combined_5x2t(const Experiment_performance* classifier1, const Experiment_performance* classifier2);

#endif //CLASSIFICATION_COMBINED5X2T_H
