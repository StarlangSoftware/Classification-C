//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#include <Memory/Memory.h>
#include "Experiment.h"

/**
 * Constructor for a specific machine learning experiment.
 * @param classifier Classifier used in the machine learning experiment
 * @param parameter Parameter(s) of the classifier.
 * @param data_set DataSet on which the classifier is run.
 * @param seed Seed of the random number generator
 * @return Allocated experiment.
 */
Experiment_ptr create_experiment(Classifier_ptr classifier, void *parameter, Data_set_ptr data_set, int seed) {
    Experiment_ptr result = malloc_(sizeof(Experiment), "create_experiment");
    result->classifier = classifier;
    result->parameter = parameter;
    result->data_set = data_set;
    result->seed = seed;
    return result;
}

/**
 * Frees memory allocated for the experiment
 * @param experiment Experiment
 */
void free_experiment(Experiment_ptr experiment) {
    free_(experiment);
}

/**
 * Construct and returns a feature selection experiment.
 * @param feature_sub_set Feature subset used in the feature selection experiment
 * @return Experiment constructed
 */
Experiment_ptr feature_selected_experiment(const Experiment *experiment, const Feature_sub_set *feature_sub_set) {
    Data_set_ptr new_data_set = get_sub_set_of_features_data_set(experiment->data_set, feature_sub_set);
    return create_experiment(experiment->classifier, experiment->parameter, new_data_set, experiment->seed);
}
