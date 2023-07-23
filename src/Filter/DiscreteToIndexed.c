//
// Created by Olcay Taner YILDIZ on 22.07.2023.
//

#include "DiscreteToIndexed.h"

/**
 * Converts discrete attributes of a single instance to indexed version.
 *
 * @param instance The instance to be converted.
 */
void convert_instance_discrete_to_indexed(Lary_filter_ptr lary_filter, Instance_ptr instance) {
    int size = attribute_size(instance);
    for (int i = 0; i < size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(lary_filter->attribute_distributions, i);
        if (size_of_distribution(distribution) != 0) {
            int index = get_index(distribution, get_attribute(instance, i)->string_value);
            add_attribute_to_instance(instance, create_discrete_indexed_attribute(index, distribution->map->hash_map->count));
        }
    }
    remove_discrete_attributes_instance(lary_filter, instance, size);
}

/**
 * Converts the data definition with discrete attributes, to data definition with DISCRETE_INDEXED attributes.
 */
void convert_data_definition_discrete_to_indexed(Lary_filter_ptr lary_filter) {
    Data_definition_ptr data_definition = lary_filter->data_set->definition;
    int size = attribute_count(data_definition);
    for (int i = 0; i < size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(lary_filter->attribute_distributions, i);
        if (size_of_distribution(distribution) != 0) {
            add_attribute(data_definition, DISCRETE_INDEXED);
        }
    }
    remove_discrete_attributes_definition(lary_filter, size);
}
