//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Memory/Memory.h>
#include "ExperimentPerformance.h"
#include "Performance.h"

/**
 * A constructor which creates a new ArrayList of Performance as results.
 */
Experiment_performance_ptr create_experiment_performance() {
    Experiment_performance_ptr result = malloc_(sizeof(Experiment_performance), "create_experiment_performance");
    result->results = create_array_list();
    result->contains_details = false;
    return result;
}

/**
 * A constructor that takes a file name as an input and takes the inputs from that file assigns these inputs to the errorRate
 * and adds them to the results ArrayList as a new Performance.
 *
 * @param fileName String input.
 */
Experiment_performance_ptr create_experiment_performance2(const char *file_name) {
    Experiment_performance_ptr result = malloc_(sizeof(Experiment_performance), "create_experiment_performance2");
    result->results = create_array_list();
    Array_list_ptr lines = read_lines(file_name);
    for (int i = 0; i < lines->size; i++){
        array_list_add(result->results, create_performance(atof(array_list_get(lines, i))));
    }
    free_array_list(lines, free_);
    return result;
}

/**
 * The add method takes a Performance as an input and adds it to the results ArrayList.
 *
 * @param performance Performance input.
 */
void add_performance(Experiment_performance_ptr experiment_performance, Performance_ptr performance) {
    array_list_add(experiment_performance->results, performance);
    experiment_performance->contains_details = false;
}

void add_detailed_performance(Experiment_performance_ptr experiment_performance,
                              Detailed_classification_performance_ptr performance) {
    array_list_add(experiment_performance->results, performance);
    experiment_performance->contains_details = true;
}

/**
 * The numberOfExperiments method returns the size of the results vector.
 *
 * @return The results vector.
 */
int number_of_experiments(const Experiment_performance* experiment_performance) {
    return experiment_performance->results->size;
}

/**
 * The getErrorRate method takes an index as an input and returns the errorRate at given index of results vector.
 *
 * @param index Index of results vector to retrieve.
 * @return The errorRate at given index of results vector.
 */
double get_error_rate(const Experiment_performance* experiment_performance, int index) {
    if (!experiment_performance->contains_details){
        Performance_ptr performance = (Performance_ptr) array_list_get(experiment_performance->results, index);
        return performance->error_rate;
    } else {
        Detailed_classification_performance_ptr performance = (Detailed_classification_performance_ptr) array_list_get(experiment_performance->results, index);
        return performance->error_rate;
    }
}

/**
 * The meanPerformance method loops through the performances of results ArrayList and sums up the errorRates of each then
 * returns a new Performance with the mean of that summation.
 *
 * @return A new Performance with the mean of the summation of errorRates.
 */
Performance_ptr mean_performance(const Experiment_performance *experiment_performance) {
    double sum_error = 0;
    for (int i = 0; i < experiment_performance->results->size; i++) {
        if (!experiment_performance->contains_details){
            Performance_ptr performance = (Performance_ptr) array_list_get(experiment_performance->results, i);
            sum_error += performance->error_rate;
        } else {
            Detailed_classification_performance_ptr performance = (Detailed_classification_performance_ptr) array_list_get(experiment_performance->results, i);
            sum_error += performance->error_rate;
        }
    }
    return create_performance(sum_error / experiment_performance->results->size);
}

/**
 * The standardDeviationPerformance method loops through the Performances of results ArrayList and returns
 * a new Performance with the standard deviation.
 *
 * @return A new Performance with the standard deviation.
 */
Performance_ptr standard_deviation_performance(const Experiment_performance *experiment_performance) {
    double sum_error_rate = 0;
    Performance_ptr average_performance;
    average_performance = mean_performance(experiment_performance);
    for (int i = 0; i < experiment_performance->results->size; i++) {
        if (!experiment_performance->contains_details){
            Performance_ptr performance = (Performance_ptr) array_list_get(experiment_performance->results, i);
            sum_error_rate += pow(performance->error_rate - average_performance->error_rate, 2);
        } else {
            Detailed_classification_performance_ptr performance = (Detailed_classification_performance_ptr) array_list_get(experiment_performance->results, i);
            sum_error_rate += pow(performance->error_rate - average_performance->error_rate, 2);
        }
    }
    return create_performance(sqrt(sum_error_rate / (experiment_performance->results->size - 1)));
}
