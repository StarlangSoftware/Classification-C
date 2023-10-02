//
// Created by Olcay Taner YILDIZ on 8.07.2023.
//

#include <stdlib.h>
#include <RandomArray.h>
#include <float.h>
#include <FileUtils.h>
#include <string.h>
#include "DecisionNode.h"
#include "../../Classifier/Classifier.h"
#include "../../InstanceList/Partition.h"

/**
 * The DecisionNode method takes {@link InstanceList} data as input and then it sets the class label parameter by finding
 * the most occurred class label of given data, it then gets distinct class labels as class labels ArrayList. Later, it adds ordered
 * indices to the indexList and shuffles them randomly. Then, it gets the class distribution of given data and finds the best entropy value
 * of these class distribution.
 * <p>
 * If an attribute of given data is {@link DiscreteIndexedAttribute}, it creates a Distribution according to discrete indexed attribute class distribution
 * and finds the entropy. If it is better than the last best entropy it reassigns the best entropy, best attribute and best split value according to
 * the newly founded best entropy's index. At the end, it also add new distribution to the class distribution .
 * <p>
 * If an attribute of given data is {@link DiscreteAttribute}, it directly finds the entropy. If it is better than the last best entropy it
 * reassigns the best entropy, best attribute and best split value according to the newly founded best entropy's index.
 * <p>
 * If an attribute of given data is {@link ContinuousAttribute}, it creates two distributions; left and right according to class distribution
 * and discrete distribution respectively, and finds the entropy. If it is better than the last best entropy it reassigns the best entropy,
 * best attribute and best split value according to the newly founded best entropy's index. At the end, it also add new distribution to
 * the right distribution and removes from left distribution .
 *
 * @param data      {@link InstanceList} input.
 * @param condition {@link DecisionCondition} to check.
 * @param parameter RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump   Refers to decision trees with only 1 splitting rule.
 */
Decision_node_ptr create_decision_node(Instance_list_ptr data,
                                       Decision_condition_ptr condition,
                                       Random_forest_parameter_ptr parameter,
                                       bool is_stump) {
    int best_attribute = -1;
    double best_split_value = 0;
    Decision_node_ptr result = malloc(sizeof(Decision_node));
    result->condition = condition;
    result->class_labels_distribution = create_discrete_distribution();
    result->children = create_array_list();
    Array_list_ptr labels = get_class_labels(data);
    for (int i = 0; i < labels->size; i++) {
        add_item(result->class_labels_distribution, array_list_get(labels, i));
    }
    result->class_label = get_maximum(labels);
    result->leaf = true;
    free_array_list(labels, NULL);
    Array_list_ptr class_labels = get_distinct_class_labels(data);
    if (class_labels->size == 1) {
        free_array_list(class_labels, NULL);
        return result;
    }
    if (is_stump && condition->attribute_index != -1) {
        free_array_list(class_labels, NULL);
        return result;
    }
    free_array_list(class_labels, NULL);
    Array_list_ptr index_list;
    int size;
    if (parameter != NULL && parameter->attribute_subset_size < attribute_size(get_instance(data, 0))) {
        index_list = index_array(attribute_size(get_instance(data, 0)), parameter->seed);
        size = parameter->attribute_subset_size;
    } else {
        index_list = create_array_list();
        for (int i = 0; i < attribute_size(get_instance(data, 0)); i++) {
            array_list_add_int(index_list, i);
        }
        size = attribute_size(get_instance(data, 0));
    }
    Discrete_distribution_ptr class_dist = class_distribution(data);
    double best_entropy = entropy(class_dist);
    for (int j = 0; j < size; j++) {
        int index = *(int *) array_list_get(index_list, j);
        if (is_discrete_indexed(get_attribute(get_instance(data, 0), index))) {
            for (int k = 0; k < get_attribute(get_instance(data, 0), index)->max_index; k++) {
                Discrete_distribution_ptr distribution = discrete_indexed_attribute_class_distribution(data, index, k);
                if (distribution->sum > 0) {
                    remove_distribution(class_dist, distribution);
                    double ent = (entropy(class_dist) * class_dist->sum + entropy(distribution) * distribution->sum) /
                                 (size_of_instance_list(data));
                    if (ent < best_entropy) {
                        best_entropy = ent;
                        best_attribute = index;
                        best_split_value = k;
                    }
                    add_distribution(class_dist, distribution);
                }
                free_discrete_distribution(distribution);
            }
        } else {
            if (is_discrete(get_attribute(get_instance(data, 0), index))) {
                double ent = entropy_for_discrete_attribute(data, index);
                if (ent < best_entropy) {
                    best_entropy = ent;
                    best_attribute = index;
                }
            } else {
                if (is_continuous(get_attribute(get_instance(data, 0), index))) {
                    sort_wrt_attribute_index(data, index);
                    double previous_value = -DBL_MAX;
                    Discrete_distribution_ptr left_distribution = class_distribution(data);
                    Discrete_distribution_ptr right_distribution = create_discrete_distribution();
                    for (int k = 0; k < size_of_instance_list(data); k++) {
                        Instance_ptr instance = get_instance(data, k);
                        if (k == 0) {
                            previous_value = get_attribute(instance, index)->float_value;
                        } else {
                            if (get_attribute(instance, index)->float_value != previous_value) {
                                double split_value = (previous_value + get_attribute(instance, index)->float_value) / 2;
                                previous_value = get_attribute(instance, index)->float_value;
                                double ent = (left_distribution->sum / size_of_instance_list(data) *
                                              entropy(left_distribution) + (right_distribution->sum /
                                                                            size_of_instance_list(data)) *
                                                                           entropy(right_distribution));
                                if (ent < best_entropy) {
                                    best_entropy = ent;
                                    best_split_value = split_value;
                                    best_attribute = index;
                                }
                            }
                        }
                        remove_item(left_distribution, instance->class_label);
                        add_item(right_distribution, instance->class_label);
                    }
                    free_discrete_distribution(left_distribution);
                    free_discrete_distribution(right_distribution);
                }
            }
        }
    }
    if (best_attribute != -1) {
        result->leaf = false;
        if (is_discrete_indexed(get_attribute(get_instance(data, 0), best_attribute))) {
            create_children_for_discrete_indexed(result, data, best_attribute, (int) best_split_value, parameter, is_stump);
        } else {
            if (is_discrete(get_attribute(get_instance(data, 0), best_attribute))) {
                create_children_for_discrete(result, data, best_attribute, parameter, is_stump);
            } else {
                if (is_continuous(get_attribute(get_instance(data, 0), best_attribute))) {
                    create_children_for_continuous(result, data, best_attribute, best_split_value, parameter, is_stump);
                }
            }
        }
    }
    free_discrete_distribution(class_dist);
    free_array_list(index_list, free);
    return result;
}

Decision_node_ptr create_decision_node2(FILE *input_file) {
    int size;
    Decision_node_ptr result = malloc(sizeof(Decision_node));
    result->condition = create_decision_condition3(input_file);
    result->children = create_array_list();
    fscanf(input_file, "%d", &size);
    if (size != 0){
        result->leaf = false;
        for (int i = 0; i < size; i++){
            Decision_node_ptr child = create_decision_node2(input_file);
            array_list_add(result->children, child);
        }
    } else {
        result->leaf = true;
        char label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", label);
        result->class_label = str_copy(result->class_label, label);
        result->class_labels_distribution = create_discrete_distribution2(input_file);
    }
    return result;
}

/**
 * The entropyForDiscreteAttribute method takes an attributeIndex and creates an ArrayList of DiscreteDistribution.
 * Then loops through the distributions and calculates the total entropy.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @return Total entropy for the discrete attribute.
 */
double entropy_for_discrete_attribute(Instance_list_ptr data, int attribute_index) {
    double sum = 0.0;
    Array_list_ptr distributions = attribute_class_distribution(data, attribute_index);
    for (int i = 0; i < distributions->size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(distributions, i);
        sum += (distribution->sum / size_of_instance_list(data)) * entropy(distribution);
    }
    free_array_list(distributions, (void (*)(void *)) free_discrete_distribution);
    return sum;
}

/**
 * The createChildrenForDiscreteIndexed method creates an ArrayList of DecisionNodes as children and a partition with respect to
 * indexed attribute.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @param attributeValue Value of the attribute.
 * @param parameter      RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump        Refers to decision trees with only 1 splitting rule.
 */
void create_children_for_discrete_indexed(Decision_node_ptr node,
                                          const Instance_list *data,
                                          int attribute_index,
                                          int attribute_value,
                                          Random_forest_parameter_ptr parameter,
                                          bool is_stump) {
    Partition_ptr children_data;
    children_data = create_partition6(data, attribute_index, attribute_value);
    Instance_list_ptr left_data = get_instance_list(children_data, 0);
    Instance_list_ptr right_data = get_instance_list(children_data, 1);
    int max_index = get_attribute(get_instance(data, 0), attribute_index)->max_index;
    Decision_condition_ptr left_condition = create_decision_condition(attribute_index,create_discrete_indexed_attribute(attribute_value, max_index));
    Decision_condition_ptr right_condition = create_decision_condition(attribute_index, create_discrete_indexed_attribute(-1, max_index));
    array_list_add(node->children, create_decision_node(left_data, left_condition, parameter, is_stump));
    array_list_add(node->children, create_decision_node(right_data, right_condition, parameter, is_stump));
    free_partition(children_data);
}

/**
 * The createChildrenForDiscrete method creates an ArrayList of values, a partition with respect to attributes and an ArrayList
 * of DecisionNodes as children.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @param parameter      RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump        Refers to decision trees with only 1 splitting rule.
 */
void create_children_for_discrete(Decision_node_ptr node,
                                  const Instance_list *data,
                                  int attribute_index,
                                  Random_forest_parameter_ptr parameter,
                                  bool is_stump) {
    Array_list_ptr value_list = get_attribute_value_list(data, attribute_index);
    Partition_ptr children_data;
    children_data = create_partition5(data, attribute_index);
    for (int i = 0; i < value_list->size; i++){
        Instance_list_ptr child_data = get_instance_list(children_data, i);
        Decision_condition_ptr condition = create_decision_condition(attribute_index, create_discrete_attribute(
                array_list_get(value_list, i)));
        array_list_add(node->children, create_decision_node(child_data, condition, parameter, is_stump));
    }
    free_array_list(value_list, NULL);
    free_partition(children_data);
}

/**
 * The createChildrenForContinuous method creates an ArrayList of DecisionNodes as children and a partition with respect to
 * continious attribute and the given split value.
 *
 * @param data InstanceList.
 * @param attributeIndex Index of the attribute.
 * @param parameter      RandomForestParameter like seed, ensembleSize, attributeSubsetSize.
 * @param isStump        Refers to decision trees with only 1 splitting rule.
 * @param splitValue     Split value is used for partitioning.
 */
void create_children_for_continuous(Decision_node_ptr node,
                                    const Instance_list *data,
                                    int attribute_index,
                                    double split_value,
                                    Random_forest_parameter_ptr parameter,
                                    bool is_stump) {
    Partition_ptr children_data;
    children_data = create_partition7(data, attribute_index, split_value);
    Instance_list_ptr left_data = get_instance_list(children_data, 0);
    Instance_list_ptr right_data = get_instance_list(children_data, 1);
    Decision_condition_ptr left_condition = create_decision_condition2(attribute_index,'<', create_continuous_attribute(split_value));
    Decision_condition_ptr right_condition = create_decision_condition2(attribute_index, '>', create_continuous_attribute(split_value));
    array_list_add(node->children, create_decision_node(left_data, left_condition, parameter, is_stump));
    array_list_add(node->children, create_decision_node(right_data, right_condition, parameter, is_stump));
    free_partition(children_data);
}

/**
 * The predict method takes an {@link Instance} as input and performs prediction on the DecisionNodes and returns the prediction
 * for that instance.
 *
 * @param instance Instance to make prediction.
 * @return The prediction for given instance.
 */
char *predict_node(const Decision_node* node, const Instance *instance) {
    if (node->leaf){
        return node->class_label;
    } else {
        for (int i = 0; i < node->children->size; i++){
            Decision_node_ptr child = array_list_get(node->children, i);
            if (satisfy(child->condition, instance)){
                return predict_node(child, instance);
            }
        }
        return node->class_label;
    }
}

Hash_map_ptr predict_probability_node(const Decision_node *node, const Instance *instance) {
    if (node->leaf){
        return get_probability_distribution(node->class_labels_distribution);
    } else {
        for (int i = 0; i < node->children->size; i++){
            Decision_node_ptr child = array_list_get(node->children, i);
            if (satisfy(child->condition, instance)){
                return predict_probability_node(child, instance);
            }
        }
        return get_probability_distribution(node->class_labels_distribution);
    }
}

void free_decision_node(Decision_node_ptr node) {
    free_discrete_distribution(node->class_labels_distribution);
    free_decision_condition(node->condition);
    if (node->children != NULL){
        for (int i = 0; i < node->children->size; i++){
            free_decision_node(array_list_get(node->children, i));
        }
        free_array_list(node->children, NULL);
    }
    free(node);
}
