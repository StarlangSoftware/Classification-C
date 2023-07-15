//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//
#include <stdlib.h>
#include <math.h>
#include <Distribution.h>
#include "Combined5x2t.h"

double
test_statistic_combined_5x2t(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double* difference;
    difference = malloc(number_of_experiments(classifier1) * sizeof(double));
    for (int i = 0; i < number_of_experiments(classifier1); i++){
        difference[i] = get_error_rate(classifier1, i) - get_error_rate(classifier2, i);
    }
    double denominator = 0;
    double numerator = 0;
    for (int i = 0; i < number_of_experiments(classifier1) / 2; i++){
        double mean = (difference[2 * i] + difference[2 * i + 1]) / 2;
        numerator += mean;
        double variance = (difference[2 * i] - mean) * (difference[2 * i] - mean) + (difference[2 * i + 1] - mean) * (difference[2 * i + 1] - mean);
        denominator += variance;
    }
    free(difference);
    numerator = sqrt(10) * numerator / 5;
    denominator = sqrt(denominator / 5);
    return numerator / denominator;
}

Statistical_test_result_ptr
compare_combined_5x2t(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double statistic = test_statistic_combined_5x2t(classifier1, classifier2);
    int degreeOfFreedom = number_of_experiments(classifier1) / 2;
    return create_statistical_test_result(tDistribution(statistic, degreeOfFreedom), false);
}

