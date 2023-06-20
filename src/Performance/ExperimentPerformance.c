//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "ExperimentPerformance.h"
#include "Performance.h"

/**
 * A constructor which creates a new {@link ArrayList} of {@link Performance} as results.
 */
Experiment_performance_ptr create_experiment_performance() {
    Experiment_performance_ptr result = malloc(sizeof(Experiment_performance));
    result->results = create_array_list();
    return result;
}

/**
 * A constructor that takes a file name as an input and takes the inputs from that file assigns these inputs to the errorRate
 * and adds them to the results {@link ArrayList} as a new {@link Performance}.
 *
 * @param fileName String input.
 */
Experiment_performance_ptr create_experiment_performance2(const char *file_name) {
    FILE* input_file;
    Experiment_performance_ptr result = malloc(sizeof(Experiment_performance));
    result->results = create_array_list();
    char line[MAX_LINE_LENGTH];
    input_file = fopen(file_name, "r");
    char* input = fgets(line, MAX_LINE_LENGTH, input_file);
    while (input != NULL){
        line[strcspn(line, "\n")] = 0;
        array_list_add(result->results, create_performance(atof(line)));
        input = fgets(line, MAX_LINE_LENGTH, input_file);
    }
    fclose(input_file);
    return result;
}

/**
 * The add method takes a {@link Performance} as an input and adds it to the results {@link ArrayList}.
 *
 * @param performance {@link Performance} input.
 */
void add_performance(Experiment_performance_ptr experiment_performance, Performance_ptr performance) {
    array_list_add(experiment_performance->results, performance);
}

/**
 * The numberOfExperiments method returns the size of the results {@link vector}.
 *
 * @return The results {@link vector}.
 */
int number_of_experiments(const Experiment_performance* experiment_performance) {
    return experiment_performance->results->size;
}

/**
 * The getErrorRate method takes an index as an input and returns the errorRate at given index of results {@link vector}.
 *
 * @param index Index of results {@link vector} to retrieve.
 * @return The errorRate at given index of results {@link vector}.
 */
double get_error_rate(const Experiment_performance* experiment_performance, int index) {
    Performance_ptr performance = array_list_get(experiment_performance->results, index);
    return performance->error_rate;
}

/**
 * The meanPerformance method loops through the performances of results {@link ArrayList} and sums up the errorRates of each then
 * returns a new {@link Performance} with the mean of that summation.
 *
 * @return A new {@link Performance} with the mean of the summation of errorRates.
 */
Performance_ptr mean_performance(const Experiment_performance *experiment_performance) {
    double sum_error = 0;
    for (int i = 0; i < experiment_performance->results->size; i++) {
        Performance_ptr performance = array_list_get(experiment_performance->results, i);
        sum_error += performance->error_rate;
    }
    return create_performance(sum_error / experiment_performance->results->size);
}

/**
 * The standardDeviationPerformance method loops through the {@link Performance}s of results {@link ArrayList} and returns
 * a new Performance with the standard deviation.
 *
 * @return A new Performance with the standard deviation.
 */
Performance_ptr standard_deviation_performance(const Experiment_performance *experiment_performance) {
    double sum_error_rate = 0;
    Performance_ptr average_performance;
    average_performance = mean_performance(experiment_performance);
    for (int i = 0; i < experiment_performance->results->size; i++) {
        Performance_ptr performance = array_list_get(experiment_performance->results, i);
        sum_error_rate += pow(performance->error_rate - average_performance->error_rate, 2);
    }
    return create_performance(sqrt(sum_error_rate / (experiment_performance->results->size - 1)));
}