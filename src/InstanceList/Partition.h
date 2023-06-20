//
// Created by Olcay Taner YILDIZ on 16.06.2023.
//

#ifndef CLASSIFICATION_PARTITION_H
#define CLASSIFICATION_PARTITION_H

#include <ArrayList.h>
#include "InstanceList.h"

struct partition{
    Array_list_ptr multi_list;
};

typedef struct partition Partition;

typedef Partition * Partition_ptr;

Partition_ptr create_partition();

Partition_ptr create_partition2(Instance_list_ptr list);

Partition_ptr create_partition3(const Instance_list* instance_list);

Partition_ptr create_partition4(Instance_list_ptr instance_list, double ratio, int seed, bool stratified);

Partition_ptr create_partition5(const Instance_list* instance_list, int attribute_index);

Partition_ptr create_partition6(const Instance_list* instance_list, int attribute_index, int attribute_value);

Partition_ptr create_partition7(const Instance_list* instance_list, int attribute_index, double split_value);

int size_of_partition(const Partition* partition);

Instance_list_ptr get_instance_list(const Partition* partition, int index);

Array_list_ptr* get_lists(const Partition* partition);

#endif //CLASSIFICATION_PARTITION_H
