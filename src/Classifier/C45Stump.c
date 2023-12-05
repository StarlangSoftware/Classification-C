//
// Created by Olcay Taner YILDIZ on 10.07.2023.
//

#include <Memory/Memory.h>
#include "C45Stump.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "C45.h"

/**
 * Training algorithm for C4.5 Stump univariate decision tree classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
Classifier_ptr train_c45_stump(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_c45_stump");
    result->model = create_decision_tree(create_decision_node(train_set, create_decision_condition4(), NULL, true));
    result->train = train_c45_stump;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

Classifier_ptr load_c45_stump(const char *file_name) {
    Classifier_ptr result = load_c45(file_name);
    result->train = train_c45_stump;
    return result;
}

void free_c45_stump(Classifier_ptr c45_stump) {
    free_c45(c45_stump);
}
