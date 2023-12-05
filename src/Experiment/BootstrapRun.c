//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//
#include <Memory/Memory.h>
#include "BootstrapRun.h"

/**
 * Execute the bootstrap run with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
Experiment_performance_ptr execute_bootstrap(const Experiment *experiment, int number_of_bootstraps) {
    Experiment_performance_ptr result = create_experiment_performance();
    for (int i = 0; i < number_of_bootstraps; i++) {
        Bootstrap_ptr bootstrap = create_bootstrap(get_instances_of_data_set(experiment->data_set), i + experiment->seed);
        Instance_list_ptr bootstrap_sample = create_instance_list3(get_sample(bootstrap));
        experiment->classifier->train(bootstrap_sample, experiment->parameter);
        add_detailed_performance(result, test_classifier(experiment->classifier, experiment->data_set->instances));
        free_bootstrap(bootstrap, NULL);
        free_(bootstrap_sample);
    }
    return result;
}

