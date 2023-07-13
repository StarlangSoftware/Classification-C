//
// Created by Olcay Taner YILDIZ on 9.07.2023.
//

#ifndef CLASSIFICATION_DECISIONTREE_H
#define CLASSIFICATION_DECISIONTREE_H

#include "DecisionNode.h"

struct decision_tree{
    Decision_node_ptr root;
};

typedef struct decision_tree Decision_tree;

typedef Decision_tree *Decision_tree_ptr;

Decision_tree_ptr create_decision_tree(Decision_node_ptr root);

Decision_tree_ptr create_decision_tree2(FILE* input_file);

void free_decision_tree(Decision_tree_ptr decision_tree);

char* predict_tree(const void *model, const Instance *instance);

void prune(Decision_tree_ptr decision_tree, const Instance_list *prune_set);

void prune_node(Decision_tree_ptr decision_tree, Decision_node_ptr node, const Instance_list *prune_set);

Hash_map_ptr predict_probability_tree(const void *model, const Instance* instance);

#endif //CLASSIFICATION_DECISIONTREE_H
