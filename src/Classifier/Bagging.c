//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#include <stdlib.h>
#include "Bagging.h"
#include "../Parameter/BaggingParameter.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "../Model/TreeEnsembleModel.h"

/**
 * Bagging bootstrap ensemble method that creates individuals for its ensemble by training each classifier on a random
 * redistribution of the training set.
 * This training method is for a bagged decision tree classifier. 20 percent of the instances are left aside for pruning of the trees
 * 80 percent of the instances are used for training the trees. The number of trees (forestSize) is a parameter, and basically
 * the method will learn an ensemble of trees as a model.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the bagging trees algorithm. ensembleSize returns the number of trees in the bagged forest.
 */
Classifier_ptr train_bagging(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    int forest_size = ((Bagging_parameter_ptr) parameter)->ensemble_size;
    Array_list_ptr forest = create_array_list();
    for (int i = 0; i < forest_size; i++){
        Bootstrap_ptr bootstrap = bootstrap_instance_list(train_set, i);
        array_list_add(forest, create_decision_tree(create_decision_node(create_instance_list3(get_sample(bootstrap)), create_decision_condition4(), NULL, false)));
    }
    result->model = create_tree_ensemble_model(forest);
    result->predict_probability = predict_probability_ensemble;
    result->predict = predict_ensemble;
    return result;
}

Classifier_ptr load_bagging(const char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_tree_ensemble_model2(file_name);
    result->predict_probability = predict_probability_ensemble;
    result->predict = predict_ensemble;
    return result;
}

void free_bagging(Classifier_ptr bagging) {
    free_tree_ensemble_model(bagging->model);
    free(bagging);
}
