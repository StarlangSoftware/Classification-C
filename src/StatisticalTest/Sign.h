//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#ifndef CLASSIFICATION_SIGN_H
#define CLASSIFICATION_SIGN_H

#include "StatisticalTestResult.h"
#include "../Performance/ExperimentPerformance.h"

int factorial(int n);

int binomial(int m, int n);

Statistical_test_result_ptr compare_sign(const Experiment_performance* classifier1, const Experiment_performance* classifier2);

#endif //CLASSIFICATION_SIGN_H
