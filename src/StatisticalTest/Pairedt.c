//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <math.h>
#include <Distribution.h>
#include "Pairedt.h"

/**
 * Calculates the test statistic of the paired t test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Given the performances of two classifiers, the test statistic of the paired t test.
 */
double test_statistic_paired_t(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double difference[number_of_experiments(classifier1)];
    double sum = 0.0;
    for (int i = 0; i < number_of_experiments(classifier1); i++){
        difference[i] = get_error_rate(classifier1, i) - get_error_rate(classifier2, i);
        sum += difference[i];
    }
    double mean = sum / number_of_experiments(classifier1);
    sum = 0.0;
    for (int i = 0; i < number_of_experiments(classifier1); i++){
        sum += (difference[i] - mean) * (difference[i] - mean);
    }
    double standardDeviation = sqrt(sum / (number_of_experiments(classifier1) - 1));
    return sqrt(number_of_experiments(classifier1)) * mean / standardDeviation;
}

/**
 * Compares two classification algorithms based on their performances (accuracy or error rate) using paired t test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Statistical test result of the comparison.
 */
Statistical_test_result_ptr
compare_paired_t(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double statistic = test_statistic_paired_t(classifier1, classifier2);
    int degreeOfFreedom = number_of_experiments(classifier1) - 1;
    return create_statistical_test_result(tDistribution(statistic, degreeOfFreedom), false);
}
