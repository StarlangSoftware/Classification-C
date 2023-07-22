//
// Created by Olcay Taner YILDIZ on 22.07.2023.
//

#include "DiscreteToContinuous.h"

/**
 * Converts discrete attributes of a single instance to continuous version using 1-of-L encoding. For example, if
 * an attribute has values red, green, blue; this attribute will be converted to 3 continuous attributes where
 * red will have the value 100, green will have the value 010, and blue will have the value 001.
 *
 * @param instance The instance to be converted.
 */
void convert_instance_discrete_to_continuous(Lary_filter_ptr lary_filter, Instance_ptr instance) {
    int size = attribute_size(instance);
    for (int i = 0; i < size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(lary_filter->attribute_distributions, i);
        if (distribution->map->hash_map->count != 0) {
            int index = get_index(distribution, get_attribute(instance, i)->string_value);
            for (int j = 0; j < size_of_distribution(distribution); j++) {
                if (j != index) {
                    add_attribute_to_instance(instance, create_continuous_attribute(0));
                } else {
                    add_attribute_to_instance(instance, create_continuous_attribute(1));
                }
            }
        }
    }
    remove_discrete_attributes_instance(lary_filter, instance, size);
}

/**
 * Converts the data definition with discrete attributes, to data definition with continuous attributes. Basically,
 * for each discrete attribute with L possible values, L more continuous attributes will be added.
 */
void convert_data_definition_discrete_to_continuous(Lary_filter_ptr lary_filter) {
    Data_definition_ptr data_definition = lary_filter->data_set->definition;
    int size = attribute_count(data_definition);
    for (int i = 0; i < size; i++) {
        Discrete_distribution_ptr distribution = array_list_get(lary_filter->attribute_distributions, i);
        if (distribution->map->hash_map->count != 0) {
            for (int j = 0; j < size_of_distribution(distribution); j++) {
                add_attribute(data_definition, CONTINUOUS);
            }
        }
    }
    remove_discrete_attributes_definition(lary_filter, size);
}
