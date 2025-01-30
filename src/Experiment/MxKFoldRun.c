//
// Created by Olcay Taner YILDIZ on 23.07.2023.
//

#include <KFoldCrossValidation.h>
#include <Memory/Memory.h>
#include "MxKFoldRun.h"

/**
 * Execute the MxKFold run with the given classifier on the given data set using the given parameters.
 *
 * @param experiment Experiment to be run.
 * @param M M in M times K run.
 * @param K K in M times K run.
 * @return An array of performances: result. result[i] is the performance of the classifier on the i'th bootstrap run.
 */
Experiment_performance_ptr execute_m_x_k_fold_run(const Experiment *experiment, int M, int K) {
    Experiment_performance_ptr result = create_experiment_performance();
    for (int j = 0; j < M; j++){
        K_fold_cross_validation_ptr cross_validation = create_k_fold_cross_validation(get_instances_of_data_set(experiment->data_set), K, experiment->seed);
        for (int i = 0; i < K; i++) {
            Instance_list_ptr train_set = create_instance_list3(get_train_fold_k_fold(cross_validation, i));
            Instance_list_ptr test_set = create_instance_list3(get_test_fold_k_fold(cross_validation, i));
            experiment->model->train(train_set, experiment->parameter);
            add_detailed_performance(result, test_classifier(experiment->model, test_set));
            free_(train_set);
            free_(test_set);
        }
        free_k_fold_cross_validation(cross_validation);
    }
    return result;
}
