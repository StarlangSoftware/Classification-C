//
// Created by Olcay Taner YILDIZ on 29.08.2024.
//

#include "DecisionStump.h"

#include <Memory/Memory.h>
#include "DecisionTree.h"

/**
 * Training algorithm for C4.5 Stump univariate decision tree classifier.
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter -Parameter of the algorithm (not used)
 */
Model_ptr train_c45_stump(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model));
    result->model = create_decision_tree(create_decision_node(train_set, create_decision_condition4(), NULL, true));
    result->train = train_c45_stump;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

/**
 * Loads the decision tree model from an input file.
 * @param file_name File name of the decision tree model.
 */
Model_ptr load_c45_stump(const char *file_name) {
    Model_ptr result = load_c45(file_name);
    result->train = train_c45_stump;
    return result;
}

/**
 * Frees memory allocated for the decision tree model
 * @param c45_stump Decision tree model
 */
void free_c45_stump(Model_ptr c45_stump) {
    free_c45(c45_stump);
}
