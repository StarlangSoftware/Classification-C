//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#include <StratifiedKFoldCrossValidation.h>
#include <Memory/Memory.h>
#include "StratifiedKFoldRunSeparateTest.h"

/**
 * Execute Stratified K-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @param K K in K fold run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th fold.
 */
Experiment_performance_ptr execute_stratified_k_fold_run_separate_test(const Experiment *experiment, int K) {
    Experiment_performance_ptr result = create_experiment_performance();
    Partition_ptr partition = create_partition4(experiment->data_set->instances, 0.25, experiment->seed, true);
    Partition_ptr class_partition = create_partition3(get_instance_list(partition, 1));
    Stratified_k_fold_cross_validation_ptr cross_validation = create_stratified_k_fold_cross_validation(get_lists(class_partition),
                                                                                                        size_of_partition(class_partition), K, experiment->seed);
    for (int i = 0; i < K; i++) {
        Instance_list_ptr train_set = create_instance_list3(get_train_fold_stratified(cross_validation, i));
        experiment->model->train(train_set, experiment->parameter);
        add_detailed_performance(result, test_classifier(experiment->model, get_instance_list(partition, 0)));
        free_(train_set);
    }
    free_stratified_k_fold_cross_validation(cross_validation);
    free_partition(class_partition);
    free_partition(partition);
    return result;
}
