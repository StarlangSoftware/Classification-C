//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <Distribution.h>
#include "Combined5x2f.h"

/**
 * Calculates the test statistic of the combined 5x2 cv F test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Given the performances of two classifiers, the test statistic of the combined 5x2 cv F test.
 */
double
test_statistic_combined_5x2f(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double difference[number_of_experiments(classifier1)];
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
    denominator *= 2;
    return numerator / denominator;
}

/**
 * Compares two classification algorithms based on their performances (accuracy or error rate) using combined 5x2 cv F test.
 * @param classifier1 Performance (error rate or accuracy) results of the first classifier.
 * @param classifier2 Performance (error rate or accuracy) results of the second classifier.
 * @return Statistical test result of the comparison.
 */
Statistical_test_result_ptr
compare_combined_5x2f(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    double statistic = test_statistic_combined_5x2f(classifier1, classifier2);
    int degreeOfFreedom1 = number_of_experiments(classifier1);
    int degreeOfFreedom2 = number_of_experiments(classifier1) / 2;
    return create_statistical_test_result(fDistribution(statistic, degreeOfFreedom1, degreeOfFreedom2), true);
}
