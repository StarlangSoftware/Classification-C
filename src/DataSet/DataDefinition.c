//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#include <string.h>
#include <Memory/Memory.h>
#include "DataDefinition.h"

/**
 * Constructor for creating a new DataDefinition.
 */
Data_definition_ptr create_data_definition() {
    Data_definition_ptr result = malloc_(sizeof(Data_definition), "create_data_definition");
    result->attribute_types = create_array_list();
    result->attribute_value_list = NULL;
    return result;
}

/**
 * Frees memory allocated for the data definition.
 * @param data_definition Data definition
 */
void free_data_definition(Data_definition_ptr data_definition) {
    if (data_definition->attribute_value_list != NULL){
        free_array_list(data_definition->attribute_value_list, (void (*)(void *)) free_array_list);
    }
    free_array_list(data_definition->attribute_types, free_);
    free_(data_definition);
}

/**
 * Constructor for creating a new DataDefinition with given attribute types.
 *
 * @param attributeTypes Attribute types of the data definition.
 */
Data_definition_ptr create_data_definition2(Array_list_ptr attribute_types) {
    Data_definition_ptr result = malloc_(sizeof(Data_definition), "create_data_definition2");
    result->attribute_types = attribute_types;
    result->attribute_value_list = NULL;
    return result;
}

/**
 * Constructor for creating a new DataDefinition with given attribute types.
 *
 * @param attributeTypes Attribute types of the data definition.
 * @param attributeValueList Array of array of strings to represent all possible values of discrete features.
 */
Data_definition_ptr create_data_definition3(Array_list_ptr attribute_types, Array_list_ptr attribute_value_list) {
    Data_definition_ptr result = malloc_(sizeof(Data_definition), "create_data_definition3");
    result->attribute_types = attribute_types;
    result->attribute_value_list = attribute_value_list;
    return result;
}

/**
 * Returns the number of attribute types.
 *
 * @return Number of attribute types.
 */
int attribute_count(const Data_definition *data_definition) {
    return data_definition->attribute_types->size;
}

/**
 * Counts the occurrences of binary and discrete type attributes.
 *
 * @return Count of binary and discrete type attributes.
 */
int discrete_attribute_count(const Data_definition *data_definition) {
    int count = 0;
    for (int i = 0; i < data_definition->attribute_types->size; i++){
        Attribute_type* attribute_type = array_list_get(data_definition->attribute_types, i);
        if (*attribute_type == DISCRETE || *attribute_type == BINARY){
            count++;
        }
    }
    return count;
}

/**
 * Counts the occurrences of binary and continuous type attributes.
 *
 * @return Count of of binary and continuous type attributes.
 */
int continuous_attribute_count(const Data_definition *data_definition) {
    int count = 0;
    for (int i = 0; i < data_definition->attribute_types->size; i++){
        Attribute_type* attribute_type = array_list_get(data_definition->attribute_types, i);
        if (*attribute_type == CONTINUOUS){
            count++;
        }
    }
    return count;
}

/**
 * Returns the attribute type of the corresponding item at given index.
 *
 * @param index Index of the attribute type.
 * @return Attribute type of the corresponding item at given index.
 */
Attribute_type get_attribute_type(const Data_definition *data_definition, int index) {
    Attribute_type * attribute_type = array_list_get(data_definition->attribute_types, index);
    return *attribute_type;
}

/**
 * Adds an attribute type to the list of attribute types.
 *
 * @param attributeType Attribute type to add to the list of attribute types.
 */
void add_attribute(Data_definition_ptr data_definition, Attribute_type attribute_type) {
    Attribute_type *type = malloc_(sizeof(Attribute_type), "add_attribute");
    *type = attribute_type;
    array_list_add(data_definition->attribute_types, type);
}

/**
 * Removes the attribute type at given index from the list of attributes.
 *
 * @param index Index to remove attribute type from list.
 */
void remove_attribute(Data_definition_ptr data_definition, int index) {
    array_list_remove(data_definition->attribute_types, index, free_);
}

/**
 * Clears all the attribute types from list.
 */
void remove_all_attributes(Data_definition_ptr data_definition) {
    array_list_clear(data_definition->attribute_types, free_);
}

/**
 * Returns number of distinct values for a given discrete attribute with index attributeIndex.
 * @param index Index of the discrete attribute.
 * @return Number of distinct values for a given discrete attribute
 */
int number_of_values(const Data_definition *data_definition, int index) {
    Array_list_ptr list = array_list_get(data_definition->attribute_value_list, index);
    return list->size;
}

/**
 * Returns the index of the given value in the values list of the attributeIndex'th discrete attribute.
 * @param attributeIndex Index of the discrete attribute.
 * @param value Value of the discrete attribute
 * @return Index of the given value in the values list of the discrete attribute.
 */
int feature_value_index(const Data_definition *data_definition, int index, const char *value) {
    Array_list_ptr list = array_list_get(data_definition->attribute_value_list, index);
    for (int i = 0; i < list->size; i++){
        if (strcmp(array_list_get(list, i), value) == 0){
            return i;
        }
    }
    return -1;
}

/**
 * Generates new subset of attribute types by using given feature subset.
 *
 * @param featureSubSet FeatureSubSet input.
 * @return DataDefinition with new subset of attribute types.
 */
Data_definition_ptr get_sub_set_of_features_data_definition(const Data_definition *data_definition,
                                                            const Feature_sub_set *feature_sub_set) {
    Array_list_ptr new_attribute_types = create_array_list();
    for (int i = 0; i < size_of_feature_sub_set(feature_sub_set); i++){
        Attribute_type* new_type = malloc_(sizeof(Attribute_type), "get_sub_set_of_features_data_definition");
        *new_type = *(Attribute_type*) array_list_get(data_definition->attribute_types, i);
        array_list_add(new_attribute_types, new_type);
    }
    return create_data_definition2(new_attribute_types);
}

Array_list_ptr construct_attribute_type_list(Attribute_type attribute_type, int count) {
    Array_list_ptr attribute_types = create_array_list();
    for (int i = 0; i < count; i++){
        Attribute_type * type = malloc_(sizeof(Attribute_type), "create_datasets_1");
        *type = attribute_type;
        array_list_add(attribute_types, type);
    }
    return attribute_types;
}
