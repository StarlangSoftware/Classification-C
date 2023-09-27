//
// Created by Olcay Taner YILDIZ on 16.06.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <FileUtils.h>
#include <string.h>
#include "DataSet.h"

/**
 * Constructor for generating a new {@link DataSet}.
 */
Data_set_ptr create_data_set() {
    Data_set_ptr result = malloc(sizeof(Data_set));
    result->instances = create_instance_list();
    result->definition = NULL;
    return result;
}

/**
 * Constructor for generating a new {@link DataSet} with given {@link DataDefinition}.
 *
 * @param definition Data definition of the data set.
 */
Data_set_ptr create_data_set2(Data_definition_ptr data_definition) {
    Data_set_ptr result = malloc(sizeof(Data_set));
    result->instances = create_instance_list();
    result->definition = data_definition;
    return result;
}

/**
 * Constructor for generating a new {@link DataSet} from given {@link ifstream}.
 *
 * @param file {@link ifstream} to generate {@link DataSet} from.
 */
Data_set_ptr create_data_set3(char *file_name) {
    FILE* input_file;
    char line[MAX_LINE_LENGTH];
    Data_set_ptr result = malloc(sizeof(Data_set));
    result->instances = create_instance_list();
    result->definition = create_data_definition();
    input_file = fopen(file_name, "r");
    char* input = fgets(line, MAX_LINE_LENGTH, input_file);
    int i = 0;
    while (input != NULL){
        line[strcspn(line, "\n")] = 0;
        Array_list_ptr attributes = str_split(line, ',');
        if (i == 0){
            for (int j = 0; j < attributes->size - 1; j++){
                char* attribute = array_list_get(attributes, j);
                atof(attribute);
                add_attribute(result->definition, CONTINUOUS);
            }
        } else {
            if (attributes->size != attribute_count(result->definition + 1)){
                continue;
            }
        }
        char* class_label = array_list_get(attributes, attributes->size - 1);
        Instance_ptr instance = create_instance2(class_label);
        for (int j = 0; j < attributes->size - 1; j++){
            char* attribute = array_list_get(attributes, j);
            switch (get_attribute_type(result->definition, j)) {
                case CONTINUOUS:
                    add_attribute_to_instance(instance, create_continuous_attribute(atof(attribute)));
                    break;
                case DISCRETE:
                    add_attribute_to_instance(instance, create_discrete_attribute(attribute));
                    break;
                case BINARY:
                case DISCRETE_INDEXED:
                    break;
            }
        }
        if (attribute_size(instance) == attribute_count(result->definition)){
            add_instance(result->instances, instance);
        }
        i++;
        input = fgets(line, MAX_LINE_LENGTH, input_file);
    }
    fclose(input_file);
    return result;
}

/**
 * Constructor for generating a new {@link DataSet} with a {@link DataDefinition}, from a {@link File} by using a separator.
 *
 * @param definition Data definition of the data set.
 * @param separator  Separator character which separates the attribute values in the data file.
 * @param fileName   Name of the data set file.
 */
Data_set_ptr create_data_set4(Data_definition_ptr data_definition, const char* separators, const char *file_name) {
    Data_set_ptr result = malloc(sizeof(Data_set));
    result->instances = create_instance_list2(data_definition, separators, file_name);
    result->definition = data_definition;
    return result;
}

/**
 * Checks the correctness of the attribute type, for instance, if the attribute of given instance is a Binary attribute,
 * and the attribute type of the corresponding item of the data definition is also a Binary attribute, it then
 * returns true, and false otherwise.
 *
 * @param instance {@link Instance} to checks the attribute type.
 * @return true if attribute types of given {@link Instance} and data definition matches.
 */
bool check_definition(const Data_set* data_set, const Instance* instance) {
    for (int i = 0; i < attribute_size(instance); i++){
        if (get_attribute(instance, i)->attribute_type == BINARY){
            if (get_attribute_type(data_set->definition, i) != BINARY){
                return false;
            }
        } else {
            if (get_attribute(instance, i)->attribute_type == DISCRETE_INDEXED){
                if (get_attribute_type(data_set->definition, i) != DISCRETE_INDEXED){
                    return false;
                }
            } else {
                if (get_attribute(instance, i)->attribute_type == DISCRETE){
                    if (get_attribute_type(data_set->definition, i) != DISCRETE){
                        return false;
                    }
                } else {
                    if (get_attribute(instance, i)->attribute_type == CONTINUOUS){
                        if (get_attribute_type(data_set->definition, i) != CONTINUOUS){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

/**
 * Adds the attribute types according to given {@link Instance}. For instance, if the attribute type of given {@link Instance}
 * is a Discrete type, it than adds a discrete attribute type to the list of attribute types.
 *
 * @param instance {@link Instance} input.
 */
void set_definition(Data_set_ptr data_set, const Instance *instance) {
    Attribute_type *type;
    Array_list_ptr attribute_types = create_array_list();
    for (int i = 0; i < attribute_size(instance); i++){
        type = malloc(sizeof(Attribute_type));
        if (get_attribute(instance, i)->attribute_type == BINARY){
            *type = BINARY;
            array_list_add(attribute_types, type);
        } else {
            if (get_attribute(instance, i)->attribute_type == DISCRETE_INDEXED){
                *type = DISCRETE_INDEXED;
                array_list_add(attribute_types, type);
            } else {
                if (get_attribute(instance, i)->attribute_type == DISCRETE){
                    *type = DISCRETE;
                    array_list_add(attribute_types, type);
                } else {
                    if (get_attribute(instance, i)->attribute_type == CONTINUOUS){
                        *type = CONTINUOUS;
                        array_list_add(attribute_types, type);
                    }
                }
            }
        }
    }
    data_set->definition = create_data_definition2(attribute_types);
}

/**
 * Returns the size of the {@link InstanceList}.
 *
 * @return Size of the {@link InstanceList}.
 */
int sample_size(const Data_set* data_set) {
    return data_set->instances->list->size;
}

/**
 * Returns the size of the class label distribution of {@link InstanceList}.
 *
 * @return Size of the class label distribution of {@link InstanceList}.
 */
int class_count(const Data_set* data_set) {
    return class_distribution(data_set->instances)->map->hash_map->count;
}

/**
 * Returns the number of attribute types at {@link DataDefinition} list.
 *
 * @return The number of attribute types at {@link DataDefinition} list.
 */
int attribute_count_of_data_set(const Data_set *data_set) {
    return attribute_count(data_set->definition);
}

/**
 * Returns the number of discrete attribute types at {@link DataDefinition} list.
 *
 * @return The number of discrete attribute types at {@link DataDefinition} list.
 */
int discrete_attribute_count_of_data_set(const Data_set *data_set) {
    return discrete_attribute_count(data_set->definition);
}

/**
 * Returns the number of continuous attribute types at {@link DataDefinition} list.
 *
 * @return The number of continuous attribute types at {@link DataDefinition} list.
 */
int continuous_attribute_count_of_data_set(const Data_set *data_set) {
    return continuous_attribute_count(data_set->definition);
}

/**
 * Adds a new instance to the {@link InstanceList}.
 *
 * @param current {@link Instance} to add.
 */
void add_instance_to_data_set(Data_set_ptr data_set, Instance_ptr current) {
    if (attribute_count(data_set->definition) == 0){
        set_definition(data_set, current);
        add_instance(data_set->instances, current);
    } else {
        if (check_definition(data_set, current)){
            add_instance(data_set->instances, current);
        }
    }
}

/**
 * Adds all the instances of given instance list to the {@link InstanceList}.
 *
 * @param instanceList {@link InstanceList} to add instances from.
 */
void add_instance_list(Data_set_ptr data_set, Array_list_ptr instance_list) {
    for (int i = 0; i < instance_list->size; i++){
        Instance_ptr instance = array_list_get(instance_list, i);
        add_instance_to_data_set(data_set, instance);
    }
}

/**
 * Returns the instances of {@link InstanceList}.
 *
 * @return The instances of {@link InstanceList}.
 */
Array_list_ptr get_instances_of_data_set(const Data_set *data_set) {
    return get_instances(data_set->instances);
}

/**
 * Returns instances of the items at the list of instance lists from the partitions.
 *
 * @return Instances of the items at the list of instance lists from the partitions.
 */
Partition_ptr get_class_instances(const Data_set *data_set) {
    return create_partition2(data_set->instances);
}

String_ptr get_classes(const Data_set *data_set) {
    Array_list_ptr class_labels = get_distinct_class_labels(data_set->instances);
    String_ptr result = create_string2(array_list_get(class_labels, 0));
    for (int i = 1; i < class_labels->size; i++){
        string_append(result, ";");
        string_append(result, array_list_get(class_labels, i));
    }
    return result;
}

void free_data_set(Data_set_ptr data_set) {
    free_instance_list(data_set->instances);
    free_data_definition(data_set->definition);
    free(data_set);
}

/**
 * Return a subset generated via the given {@link FeatureSubSet}.
 *
 * @param featureSubSet {@link FeatureSubSet} input.
 * @return Subset generated via the given {@link FeatureSubSet}.
 */
Data_set_ptr get_sub_set_of_features_data_set(const Data_set *data_set, const Feature_sub_set *feature_sub_set) {
    Data_definition_ptr data_definition = get_sub_set_of_features_data_definition(data_definition, feature_sub_set);
    Data_set_ptr result = create_data_set2(data_definition);
    for (int i = 0; i < size_of_instance_list(data_set->instances); i++){
        Instance_ptr instance = get_instance(data_set->instances, i);
        add_instance_to_data_set(result, get_sub_set_of_features_instance(instance, feature_sub_set));
    }
    return result;
}
