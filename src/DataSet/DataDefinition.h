//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#ifndef CLASSIFICATION_DATADEFINITION_H
#define CLASSIFICATION_DATADEFINITION_H

#include <ArrayList.h>
#include "../Attribute/AttributeType.h"
#include "../FeatureSelection/FeatureSubSet.h"

struct data_definition{
    Array_list_ptr attribute_types;
    Array_list_ptr attribute_value_list;
};

typedef struct data_definition Data_definition;

typedef Data_definition *Data_definition_ptr;

Data_definition_ptr create_data_definition();

Data_definition_ptr create_data_definition2(Array_list_ptr attribute_types);

Data_definition_ptr create_data_definition3(Array_list_ptr attribute_types, Array_list_ptr attribute_value_list);

void free_data_definition(Data_definition_ptr data_definition);

int attribute_count(const Data_definition* data_definition);

int discrete_attribute_count(const Data_definition* data_definition);

int continuous_attribute_count(const Data_definition* data_definition);

Attribute_type get_attribute_type(const Data_definition* data_definition, int index);

void add_attribute(Data_definition_ptr data_definition, Attribute_type attribute_type);

void remove_attribute(Data_definition_ptr data_definition, int index);

void remove_all_attributes(Data_definition_ptr data_definition);

int number_of_values(const Data_definition* data_definition, int index);

int feature_value_index(const Data_definition* data_definition, int index, const char* value);

Data_definition_ptr get_sub_set_of_features_data_definition(const Data_definition* data_definition, const Feature_sub_set* feature_sub_set);

Array_list_ptr construct_attribute_type_list(Attribute_type attribute_type, int count);

#endif //CLASSIFICATION_DATADEFINITION_H
