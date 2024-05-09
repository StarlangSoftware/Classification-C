//
// Created by Olcay Taner YILDIZ on 10.07.2023.
//

#include <Memory/Memory.h>
#include "C45.h"
#include "../Parameter/C45Parameter.h"
#include "../InstanceList/Partition.h"

/**
 * Training algorithm for C4.5 univariate decision tree classifier. 20 percent of the data are left aside for pruning
 * 80 percent of the data is used for constructing the tree.
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter -
 */
Classifier_ptr train_c45(Instance_list_ptr train_set, const void *parameter) {
    Decision_tree_ptr tree;
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_c45");
    C45_parameter_ptr c45_parameter = (C45_parameter_ptr) parameter;
    if (c45_parameter->prune){
        Partition_ptr partition = create_partition4(train_set, c45_parameter->cross_validation_ratio, c45_parameter->seed, true);
        tree = create_decision_tree(create_decision_node(get_instance_list(partition, 1), create_decision_condition4(), NULL, false));
        prune(tree, get_instance_list(partition, 0));
        free_partition(partition);
    } else {
        tree = create_decision_tree(create_decision_node(train_set, create_decision_condition4(), NULL, false));
    }
    result->model = tree;
    result->train = train_c45;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

/**
 * Loads the decision tree model from an input file.
 * @param file_name File name of the decision tree model.
 */
Classifier_ptr load_c45(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_c45");
    FILE* input_file = fopen(file_name, "r");
    result->model = create_decision_tree2(input_file);
    fclose(input_file);
    result->train = train_c45;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

/**
 * Frees memory allocated to decision tree model
 * @param c45 Decision tree model
 */
void free_c45(Classifier_ptr c45) {
    free_decision_tree(c45->model);
    free_(c45);
}

Classifier_ptr validation_c45(Decision_tree_ptr decision_tree) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "validation_c45");
    result->model = decision_tree;
    result->train = train_c45;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}
