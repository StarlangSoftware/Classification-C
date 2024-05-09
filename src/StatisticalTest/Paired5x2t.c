//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <math.h>
#include <Distribution.h>
#include "Paired5x2t.h"

/**
 * Calculates the test statistic of the 5x2 t test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Given the performances of two classifiers, the test statistic of the 5x2 t test.
 */
double
test_statistic_paired_5x2t(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double difference[number_of_experiments(classifier1)];
    for (int i = 0; i < number_of_experiments(classifier1); i++){
        difference[i] = get_error_rate(classifier1, i) - get_error_rate(classifier2, i);
    }
    double denominator = 0;
    for (int i = 0; i < number_of_experiments(classifier1) / 2; i++){
        double mean = (difference[2 * i] + difference[2 * i + 1]) / 2;
        double variance = (difference[2 * i] - mean) * (difference[2 * i] - mean) + (difference[2 * i + 1] - mean) * (difference[2 * i + 1] - mean);
        denominator += variance;
    }
    denominator = sqrt(denominator / 5);
    double result = difference[0] / denominator;
    return result;
}

/**
 * Compares two classification algorithms based on their performances (accuracy or error rate) using 5x2 t test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Statistical test result of the comparison.
 */
Statistical_test_result_ptr
compare_paired_5x2t(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double statistic = test_statistic_paired_5x2t(classifier1, classifier2);
    int degreeOfFreedom = number_of_experiments(classifier1) / 2;
    return create_statistical_test_result(tDistribution(statistic, degreeOfFreedom), false);
}
