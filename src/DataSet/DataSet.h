//
// Created by Olcay Taner YILDIZ on 16.06.2023.
//

#ifndef CLASSIFICATION_DATASET_H
#define CLASSIFICATION_DATASET_H

#include "../InstanceList/InstanceList.h"
#include "../InstanceList/Partition.h"

struct data_set{
    Instance_list_ptr instances;
    Data_definition_ptr definition;
};

typedef struct data_set Data_set;

typedef Data_set *Data_set_ptr;

Data_set_ptr create_data_set();

Data_set_ptr create_data_set2(Data_definition_ptr data_definition);

Data_set_ptr create_data_set3(char* file_name);

Data_set_ptr create_data_set4(Data_definition_ptr data_definition, const char* separator, const char* file_name);

void free_data_set(Data_set_ptr data_set);

bool check_definition(const Data_set* data_set, const Instance* instance);

void set_definition(Data_set_ptr data_set, const Instance* instance);

int sample_size(const Data_set* data_set);

int class_count(const Data_set* data_set);

int attribute_count_of_data_set(const Data_set* data_set);

int discrete_attribute_count_of_data_set(const Data_set* data_set);

int continuous_attribute_count_of_data_set(const Data_set* data_set);

void add_instance_to_data_set(Data_set_ptr data_set, Instance_ptr current);

void add_instance_list(Data_set_ptr data_set, Array_list_ptr instance_list);

Array_list_ptr get_instances_of_data_set(const Data_set* data_set);

Partition_ptr get_class_instances(const Data_set* data_set);

String_ptr get_classes(const Data_set* data_set);

#endif //CLASSIFICATION_DATASET_H
