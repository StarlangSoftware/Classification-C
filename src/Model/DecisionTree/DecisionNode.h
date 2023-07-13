//
// Created by Olcay Taner YILDIZ on 8.07.2023.
//

#ifndef CLASSIFICATION_DECISIONNODE_H
#define CLASSIFICATION_DECISIONNODE_H

#include <ArrayList.h>
#include <DiscreteDistribution.h>
#include "DecisionCondition.h"
#include "../../InstanceList/InstanceList.h"
#include "../../Parameter/RandomForestParameter.h"

struct decision_node{
    Array_list_ptr children;
    char* class_label;
    bool leaf;
    Discrete_distribution_ptr class_labels_distribution;
    Decision_condition_ptr condition;
};

typedef struct decision_node Decision_node;

typedef Decision_node *Decision_node_ptr;

Decision_node_ptr create_decision_node(Instance_list_ptr data,
                                       Decision_condition_ptr condition,
                                       Random_forest_parameter_ptr parameter,
                                       bool is_stump);

Decision_node_ptr create_decision_node2(FILE* input_file);

void free_decision_node(Decision_node_ptr node);

double entropy_for_discrete_attribute(Instance_list_ptr data, int attribute_index);

void create_children_for_discrete_indexed(Decision_node_ptr node,
                                          const Instance_list* data,
                                          int attribute_index,
                                          int attribute_value,
                                          Random_forest_parameter_ptr parameter,
                                          bool is_stump);

void create_children_for_discrete(Decision_node_ptr node,
                                  const Instance_list* data,
                                  int attribute_index,
                                  Random_forest_parameter_ptr parameter,
                                  bool is_stump);

void create_children_for_continuous(Decision_node_ptr node,
                                    const Instance_list* data,
                                    int attribute_index,
                                    double split_value,
                                    Random_forest_parameter_ptr parameter,
                                    bool is_stump);

char* predict_node(const Decision_node* node, const Instance* instance);

Hash_map_ptr predict_probability_node(const Decision_node* node, const Instance* instance);

#endif //CLASSIFICATION_DECISIONNODE_H
