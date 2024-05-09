//
// Created by Olcay Taner YILDIZ on 16.06.2023.
//

#include <CounterHashMap.h>
#include <RandomArray.h>
#include <Memory/Memory.h>
#include "Partition.h"

/**
 * Constructor for generating a partition.
 */
Partition_ptr create_partition() {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition");
    result->multi_list = create_array_list();
    return result;
}

/**
 * Adds given instance list to the list of instance lists.
 *
 * @param list Instance list to add.
 */
Partition_ptr create_partition2(Instance_list_ptr list) {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition2");
    result->multi_list = create_array_list();
    array_list_add(result->multi_list, list);
    return result;
}

/**
 * Returns the size of the list of instance lists.
 *
 * @return The size of the list of instance lists.
 */
int size_of_partition(const Partition *partition) {
    return partition->multi_list->size;
}

/**
 * Returns the corresponding instance list at given index of list of instance lists.
 *
 * @param index Index of the instance list.
 * @return Instance list at given index of list of instance lists.
 */
Instance_list_ptr get_instance_list(const Partition *partition, int index) {
    return array_list_get(partition->multi_list, index);
}

/**
 * Returns the instances of the items at the list of instance lists.
 *
 * @return Instances of the items at the list of instance lists.
 */
Array_list_ptr *get_lists(const Partition *partition) {
    Array_list_ptr* result = malloc_(partition->multi_list->size * sizeof(Array_list_ptr), "get_lists");
    for (int i = 0; i < partition->multi_list->size; i++){
        Instance_list_ptr instance_list = array_list_get(partition->multi_list, i);
        result[i] = get_instances(instance_list);
    }
    return result;
}

/**
 * Divides the instances in the instance instance_list into partitions so that all instances of a class are grouped in a
 * single partition.
 *
 * @return Groups of instances according to their class labels.
 */
Partition_ptr create_partition3(const Instance_list* instance_list) {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition3");
    result->multi_list = create_array_list();
    Array_list_ptr class_labels = get_distinct_class_labels(instance_list);
    for (int i = 0; i < class_labels->size; i++){
        array_list_add(result->multi_list, create_instance_list());
    }
    for (int i = 0; i < instance_list->list->size; i++){
        Instance_ptr instance = get_instance(instance_list, i);
        int index = array_list_index_of(class_labels, instance->class_label,
                                        (int (*)(const void *, const void *)) compare_string);
        add_instance(get_instance_list(result, index), instance);
    }
    free_array_list(class_labels, NULL);
    return result;
}

/**
 * Creates a stratified/not-stratified partition of the current instance list. In a stratified partition, the percentage of each
 * class is preserved. For example, let's say there are three classes in the instance list, and let the percentages of
 * these classes be %20, %30, and %50; then the percentages of these classes in the stratified partitions are the
 * same, that is, %20, %30, and %50.
 *
 * @param ratio Ratio of the stratified partition. Ratio is between 0 and 1. If the ratio is 0.2, then 20 percent
 *              of the instances are put in the first group, 80 percent of the instances are put in the second group.
 * @param random random is used as a random number.
 * @return 2 group stratified partition of the instances in this instance list.
 */
Partition_ptr create_partition4(Instance_list_ptr instance_list, double ratio, int seed, bool stratified) {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition4");
    result->multi_list = create_array_list();
    array_list_add(result->multi_list, create_instance_list());
    array_list_add(result->multi_list, create_instance_list());
    if (stratified){
        Counter_hash_map_ptr counts = create_counter_hash_map(
                (unsigned int (*)(const void *, int)) hash_function_string,
                (int (*)(const void *, const void *)) compare_string);
        Discrete_distribution_ptr distribution;
        distribution = class_distribution(instance_list);
        Array_list_ptr random_array = index_array(size_of_instance_list(instance_list), seed);
        for (int i = 0; i < size_of_instance_list(instance_list); i++){
            int index = *(int*)array_list_get(random_array, i);
            Instance_ptr instance = get_instance(instance_list, index);
            if (count_counter_hash_map(counts, instance->class_label) < size_of_instance_list(instance_list) * ratio *
                                                                                get_probability(distribution, instance->class_label)){
                add_instance(get_instance_list(result, 0), instance);
            } else {
                add_instance(get_instance_list(result, 1), instance);
            }
            put_counter_hash_map(counts, instance->class_label);
        }
        free_discrete_distribution(distribution);
        free_counter_hash_map(counts);
        free_array_list(random_array, free_);
    } else {
        shuffle_instance_list(instance_list, seed);
        for (int i = 0; i < size_of_instance_list(instance_list); i++) {
            Instance_ptr instance = get_instance(instance_list, i);
            if (i < size_of_instance_list(instance_list) * ratio){
                add_instance(get_instance_list(result, 0), instance);
            } else {
                add_instance(get_instance_list(result, 1), instance);
            }
        }
    }
    return result;
}

/**
 * Creates a partition depending on the distinct values of a discrete attribute. If the discrete attribute has 4
 * distinct values, the resulting partition will have 4 groups, where each group contain instance whose
 * values of that discrete attribute are the same.
 *
 * @param attributeIndex Index of the discrete attribute.
 * @return L groups of instances, where L is the number of distinct values of the discrete attribute with index
 * attributeIndex.
 */
Partition_ptr create_partition5(const Instance_list *instance_list, int attribute_index) {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition5");
    result->multi_list = create_array_list();
    Array_list_ptr value_list = get_attribute_value_list(instance_list, attribute_index);
    for (int i = 0; i < value_list->size; i++){
        array_list_add(result->multi_list, create_instance_list());
    }
    for (int i = 0; i < instance_list->list->size; i++) {
        Instance_ptr instance = get_instance(instance_list, i);
        char* attribute_value = get_attribute(instance, attribute_index)->string_value;
        int index = array_list_index_of(value_list, attribute_value,
                                        (int (*)(const void *, const void *)) compare_string);
        add_instance(get_instance_list(result, index), instance);
    }
    free_array_list(value_list, NULL);
    return result;
}

/**
 * Creates a partition depending on the distinct values of a discrete indexed attribute.
 *
 * @param attributeIndex Index of the discrete indexed attribute.
 * @param attributeValue Value of the attribute.
 * @return L groups of instances, where L is the number of distinct values of the discrete indexed attribute with index
 * attributeIndex and value attributeValue.
 */
Partition_ptr create_partition6(const Instance_list *instance_list, int attribute_index, int attribute_value) {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition6");
    result->multi_list = create_array_list();
    array_list_add(result->multi_list, create_instance_list());
    array_list_add(result->multi_list, create_instance_list());
    for (int i = 0; i < instance_list->list->size; i++) {
        Instance_ptr instance = get_instance(instance_list, i);
        int current_attribute_value = get_attribute(instance, attribute_index)->int_value;
        if (current_attribute_value == attribute_value){
            add_instance(get_instance_list(result, 0), instance);
        } else {
            add_instance(get_instance_list(result, 1), instance);
        }
    }
    return result;
}

/**
 * Creates a two group partition depending on the values of a continuous attribute. If the value of the attribute is
 * less than splitValue, the instance is forwarded to the first group, else it is forwarded to the second group.
 *
 * @param instance_list Instance list for which partition will be created.
 * @param attribute_index Index of the continuous attribute
 * @param split_value     Threshold to divide instances
 */
Partition_ptr create_partition7(const Instance_list *instance_list, int attribute_index, double split_value) {
    Partition_ptr result = malloc_(sizeof(Partition), "create_partition7");
    result->multi_list = create_array_list();
    array_list_add(result->multi_list, create_instance_list());
    array_list_add(result->multi_list, create_instance_list());
    for (int i = 0; i < instance_list->list->size; i++) {
        Instance_ptr instance = get_instance(instance_list, i);
        double current_attribute_value = get_attribute(instance, attribute_index)->float_value;
        if (current_attribute_value <= split_value){
            add_instance(get_instance_list(result, 0), instance);
        } else {
            add_instance(get_instance_list(result, 1), instance);
        }
    }
    return result;
}

/**
 * Frees memory allocated for partition.
 * @param partition Partiiton
 */
void free_partition(Partition_ptr partition) {
    for (int i = 0; i < partition->multi_list->size; i++){
        Instance_list_ptr  list = get_instance_list(partition, i);
        free_array_list(list->list, NULL);
        free_(list);
    }
    free_array_list(partition->multi_list, NULL);
    free_(partition);
}
