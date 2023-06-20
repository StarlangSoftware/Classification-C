//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#ifndef CLASSIFICATION_INSTANCELIST_H
#define CLASSIFICATION_INSTANCELIST_H

#include <ArrayList.h>
#include <Bootstrap.h>
#include <DiscreteDistribution.h>
#include <Matrix.h>
#include "../DataSet/DataDefinition.h"
#include "../Instance/Instance.h"

struct instance_list{
    Array_list_ptr list;
};

typedef struct instance_list Instance_list;

typedef Instance_list *Instance_list_ptr;

Instance_list_ptr create_instance_list();

Instance_list_ptr create_instance_list2(const Data_definition* definition, const char *separators, const char* file_name);

Instance_list_ptr create_instance_list3(Array_list_ptr list);

void free_instance_list(Instance_list_ptr instance_list);

void add_instance(Instance_list_ptr instance_list, Instance_ptr instance);

void add_all_instances(Instance_list_ptr instance_list, const Array_list* instances_added);

int size_of_instance_list(const Instance_list* instance_list);

Instance_ptr get_instance(const Instance_list* instance_list, int index);

void sort_wrt_class_labels(Instance_list_ptr instance_list);

void shuffle_instance_list(Instance_list_ptr instance_list, int seed);

Bootstrap_ptr bootstrap_instance_list(Instance_list_ptr instance_list, int seed);

Array_list_ptr get_class_labels(const Instance_list* instance_list);

Array_list_ptr get_distinct_class_labels(const Instance_list* instance_list);

Array_list_ptr get_instances(Instance_list_ptr instance_list);

Array_list_ptr get_attribute_value_list(const Instance_list* instance_list, int attribute_index);

Attribute_ptr attribute_average(const Instance_list* instance_list, int attribute_index);

Array_list_ptr continuous_attribute_average(const Instance_list* instance_list, int attribute_index);

Attribute_ptr attribute_standard_deviation(const Instance_list* instance_list, int attribute_index);

Array_list_ptr continuous_attribute_standard_deviation(const Instance_list* instance_list, int attribute_index);

Discrete_distribution_ptr attribute_distribution(const Instance_list* instance_list, int attribute_index);

Array_list_ptr attribute_class_distribution(const Instance_list* instance_list, int attribute_index);

Discrete_distribution_ptr discrete_indexed_attribute_class_distribution(const Instance_list* instance_list, int attribute_index, int attribute_value);

Discrete_distribution_ptr class_distribution(const Instance_list* instance_list);

Array_list_ptr all_attributes_distribution(const Instance_list* instance_list);

Instance_ptr average(const Instance_list* instance_list);

Array_list_ptr continuous_attribute_average2(const Instance_list* instance_list);

Instance_ptr standard_deviation(const Instance_list* instance_list);

Array_list_ptr continuous_attribute_standard_deviation2(const Instance_list* instance_list);

Matrix_ptr covariance(const Instance_list *instance_list, const Vector* average);

void clear(Instance_list_ptr instance_list);

#endif //CLASSIFICATION_INSTANCELIST_H
