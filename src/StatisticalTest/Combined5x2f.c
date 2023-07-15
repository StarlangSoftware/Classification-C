//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <stdlib.h>
#include <Distribution.h>
#include "Combined5x2f.h"

double
test_statistic_combined_5x2f(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double* difference;
    difference = malloc(number_of_experiments(classifier1) * sizeof(double));
    double numerator = 0;
    for (int i = 0; i < number_of_experiments(classifier1); i++){
        difference[i] = get_error_rate(classifier1, i) - get_error_rate(classifier2, i);
        numerator += difference[i] * difference[i];
    }
    double denominator = 0;
    for (int i = 0; i < number_of_experiments(classifier1) / 2; i++){
        double mean = (difference[2 * i] + difference[2 * i + 1]) / 2;
        double variance = (difference[2 * i] - mean) * (difference[2 * i] - mean) + (difference[2 * i + 1] - mean) * (difference[2 * i + 1] - mean);
        denominator += variance;
    }
    free(difference);
    denominator *= 2;
    return numerator / denominator;
}

Statistical_test_result_ptr
compare_combined_5x2f(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double statistic = test_statistic_combined_5x2f(classifier1, classifier2);
    int degreeOfFreedom1 = number_of_experiments(classifier1);
    int degreeOfFreedom2 = number_of_experiments(classifier1) / 2;
    return create_statistical_test_result(fDistribution(statistic, degreeOfFreedom1, degreeOfFreedom2), true);
}
