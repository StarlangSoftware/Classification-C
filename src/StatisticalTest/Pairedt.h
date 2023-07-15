//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#ifndef CLASSIFICATION_PAIREDT_H
#define CLASSIFICATION_PAIREDT_H

#include "../Performance/ExperimentPerformance.h"
#include "StatisticalTestResult.h"

double test_statistic_paired_t(const Experiment_performance* classifier1, const Experiment_performance* classifier2);

Statistical_test_result_ptr compare_paired_t(const Experiment_performance* classifier1, const Experiment_performance* classifier2);

#endif //CLASSIFICATION_PAIREDT_H
