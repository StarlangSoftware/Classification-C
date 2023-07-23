//
// Created by Olcay Taner YILDIZ on 10.07.2023.
//

#include <stdlib.h>
#include "C45.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "../Parameter/C45Parameter.h"
#include "../InstanceList/Partition.h"

Classifier_ptr train_c45(Instance_list_ptr train_set, const void *parameter) {
    Decision_tree_ptr tree;
    Classifier_ptr result = malloc(sizeof(Classifier));
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

Classifier_ptr load_c45(const char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    FILE* input_file = fopen(file_name, "r");
    result->model = create_decision_tree2(input_file);
    fclose(input_file);
    result->train = train_c45;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

void free_c45(Classifier_ptr c45) {
    free_decision_tree(c45->model);
    free(c45);
}

Classifier_ptr validation_c45(Decision_tree_ptr decision_tree) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = decision_tree;
    result->train = train_c45;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}
