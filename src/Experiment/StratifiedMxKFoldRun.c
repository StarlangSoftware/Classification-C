//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#include <StratifiedKFoldCrossValidation.h>
#include <Memory/Memory.h>
#include "StratifiedMxKFoldRun.h"

/**
 * Execute the Stratified MxK-fold cross-validation with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
Experiment_performance_ptr execute_stratified_m_x_k_fold_run(const Experiment *experiment, int M, int K) {
    Experiment_performance_ptr result = create_experiment_performance();
    for (int j = 0; j < M; j++){
        Partition_ptr partition = create_partition3(experiment->data_set->instances);
        Stratified_k_fold_cross_validation_ptr cross_validation = create_stratified_k_fold_cross_validation(get_lists(partition),
                                                                                                            size_of_partition(partition),
                                                                                                            K, experiment->seed);
        for (int i = 0; i < K; i++) {
            Instance_list_ptr train_set = create_instance_list3(get_train_fold_stratified(cross_validation, i));
            Instance_list_ptr test_set = create_instance_list3(get_test_fold_stratified(cross_validation, i));
            experiment->model->train(train_set, experiment->parameter);
            add_detailed_performance(result, test_classifier(experiment->model, test_set));
            free_(train_set);
            free_(test_set);
        }
        free_stratified_k_fold_cross_validation(cross_validation);
        free_partition(partition);
    }
    return result;
}
