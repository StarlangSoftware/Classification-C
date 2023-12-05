//
// Created by Olcay Taner YILDIZ on 9.07.2023.
//

#include <Memory/Memory.h>
#include "DecisionTree.h"
#include "../../Classifier/Classifier.h"
#include "../../Classifier/C45.h"

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

Decision_tree_ptr create_decision_tree2(FILE *input_file) {
    Decision_tree_ptr result = malloc_(sizeof(Decision_tree), "create_decision_tree2");
    result->root = create_decision_node2(input_file);
    return result;
}

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
    Classifier_ptr classifier = validation_c45(decision_tree);
    Detailed_classification_performance_ptr before = test_classifier(classifier, prune_set);
    node->leaf = true;
    Detailed_classification_performance_ptr after = test_classifier(classifier, prune_set);
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
    free_(classifier);
}

Hash_map_ptr predict_probability_tree(const void *model, const Instance *instance) {
    Decision_tree_ptr decision_tree = (Decision_tree_ptr) model;
    return predict_probability_node(decision_tree->root, instance);
}
