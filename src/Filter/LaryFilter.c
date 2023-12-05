//
// Created by Olcay Taner YILDIZ on 22.07.2023.
//
#include <Memory/Memory.h>
#include "LaryFilter.h"

/**
 * Constructor that sets the dataSet and all the attributes distributions.
 *
 * @param dataSet DataSet that will bu used.
 */
Lary_filter_ptr create_lary_filter(Data_set_ptr data_set) {
    Lary_filter_ptr result = malloc_(sizeof(Lary_filter), "create_lary_filter");
    result->data_set = data_set;
    result->attribute_distributions = all_attributes_distribution(data_set->instances);
    return result;
}

void free_lary_filter(Lary_filter_ptr lary_filter) {
    free_array_list(lary_filter->attribute_distributions, (void (*)(void *)) free_discrete_distribution);
    free_(lary_filter);
}

/**
 * The removeDiscreteAttributes method takes an Instance as an input, and removes the discrete attributes from
 * given instance.
 *
 * @param instance Instance to removes attributes from.
 * @param size     Size of the given instance.
 */
void remove_discrete_attributes_instance(Lary_filter_ptr lary_filter, Instance_ptr instance, int size) {
    int k = 0;
    for (int i = 0; i < size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(lary_filter->attribute_distributions, i);
        if (size_of_distribution(distribution) != 0) {
            remove_attribute_from_instance(instance, k);
        } else {
            k++;
        }
    }
}

/**
 * The removeDiscreteAttributes method removes the discrete attributes from dataDefinition.
 *
 * @param size Size of item that attributes will be removed.
 */
void remove_discrete_attributes_definition(Lary_filter_ptr lary_filter, int size) {
    Data_definition_ptr dataDefinition = lary_filter->data_set->definition;
    int k = 0;
    for (int i = 0; i < size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(lary_filter->attribute_distributions, i);
        if (size_of_distribution(distribution) != 0) {
            remove_attribute(dataDefinition, k);
        } else {
            k++;
        }
    }
}

/**
 * Feature converter for a list of instances. Using the abstract method convertInstance, each instance in the
 * instance list will be converted.
 */
void convert_with_lary_filter(Lary_filter_ptr lary_filter, void *(*convert_instance)(Lary_filter_ptr lary_filter, Instance_ptr),
                              void *convert_data_definition(Lary_filter_ptr lary_filter)) {
    Array_list_ptr instances = get_instances_of_data_set(lary_filter->data_set);
    for (int i = 0; i < instances->size; i++){
        Instance_ptr instance = array_list_get(instances, i);
        convert_instance(lary_filter, instance);
    }
    convert_data_definition(lary_filter);
}

