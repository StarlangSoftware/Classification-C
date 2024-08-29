//
// Created by Olcay Taner YILDIZ on 9.07.2023.
//

#include <Memory/Memory.h>
#include "DecisionTree.h"
#include "../../Parameter/C45Parameter.h"
#include "../../InstanceList/Partition.h"

/**
 * Constructor that sets root node of the decision tree.
 *
 * @param root DecisionNode type input.
 */
Decision_tree_ptr create_decision_tree(Decision_node_ptr root) {
    Decision_tree_ptr result = malloc_(sizeof(Decision_tree), "create_decision_tree");
    result->root = root;
    return result;
}

/**
 * Loads a decision tree model from an input model file.
 * @param input_file Model file.
 */
Decision_tree_ptr create_decision_tree2(FILE *input_file) {
    Decision_tree_ptr result = malloc_(sizeof(Decision_tree), "create_decision_tree2");
    result->root = create_decision_node2(input_file);
    return result;
}

/**
 * Frees memory allocated for decision tree
 * @param decision_tree Decision tree
 */
void free_decision_tree(Decision_tree_ptr decision_tree) {
    free_decision_node(decision_tree->root);
    free_(decision_tree);
}

/**
 * The predict method  performs prediction on the root node of given instance, and if it is null, it returns the possible class labels.
 * Otherwise it returns the returned class labels.
 *
 * @param instance Instance make prediction.
 * @return Possible class labels.
 */
char *predict_tree(const void *model, const Instance *instance) {
    Decision_tree_ptr decision_tree = (Decision_tree_ptr) model;
    return predict_node(decision_tree->root, instance);
}

/**
 * The prune method takes an InstanceList and  performs pruning to the root node.
 *
 * @param pruneSet InstanceList to perform pruning.
 */
void prune(Decision_tree_ptr decision_tree, const Instance_list *prune_set) {
    prune_node(decision_tree, decision_tree->root, prune_set);
}

/**
 * The prune method takes a DecisionNode and an InstanceList as inputs. It checks the classification performance
 * of given InstanceList before pruning, i.e making a node leaf, and after pruning. If the after performance is better than the
 * before performance it prune the given InstanceList from the tree.
 *
 * @param tree     DecisionTree that will be pruned if conditions hold.
 * @param pruneSet Small subset of tree that will be removed from tree.
 */
void prune_node(Decision_tree_ptr decision_tree, Decision_node_ptr node, const Instance_list *prune_set) {
    if (node->leaf){
        return;
    }
    Model_ptr model_c45 = validation_c45(decision_tree);
    Detailed_classification_performance_ptr before = test_classifier(model_c45, prune_set);
    node->leaf = true;
    Detailed_classification_performance_ptr after = test_classifier(model_c45, prune_set);
    if (after->accuracy < before->accuracy){
        node->leaf = false;
        for (int i = 0; i < node->children->size; i++){
            Decision_node_ptr child = array_list_get(node->children, i);
            prune_node(decision_tree, child, prune_set);
        }
    } else{
        for (int i = 0; i < node->children->size; i++){
            Decision_node_ptr child = array_list_get(node->children, i);
            free_decision_node(child);
        }
        free_array_list(node->children, NULL);
        node->children = NULL;
    }
    free_detailed_classification_performance(before);
    free_detailed_classification_performance(after);
    free_(model_c45);
}

/**
 * Calculates the posterior probability distribution for the given instance according to Decision tree model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr predict_probability_tree(const void *model, const Instance *instance) {
    Decision_tree_ptr decision_tree = (Decision_tree_ptr) model;
    return predict_probability_node(decision_tree->root, instance);
}

/**
 * Training algorithm for C4.5 univariate decision tree classifier. 20 percent of the data are left aside for pruning
 * 80 percent of the data is used for constructing the tree.
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter -
 */
Model_ptr train_c45(Instance_list_ptr train_set, const void *parameter) {
    Decision_tree_ptr tree;
    Model_ptr result = malloc_(sizeof(Model), "train_c45");
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
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

/**
 * Loads the decision tree model from an input file.
 * @param file_name File name of the decision tree model.
 */
Model_ptr load_c45(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_c45");
    FILE* input_file = fopen(file_name, "r");
    result->model = create_decision_tree2(input_file);
    result->train = train_c45;
    fclose(input_file);
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}

/**
 * Frees memory allocated to decision tree model
 * @param c45 Decision tree model
 */
void free_c45(Model_ptr c45) {
    free_decision_tree(c45->model);
    free_(c45);
}

Model_ptr validation_c45(Decision_tree_ptr decision_tree) {
    Model_ptr result = malloc_(sizeof(Model), "validation_c45");
    result->model = decision_tree;
    result->train = train_c45;
    result->predict_probability = predict_probability_tree;
    result->predict = predict_tree;
    return result;
}
