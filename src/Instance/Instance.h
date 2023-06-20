//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#ifndef CLASSIFICATION_INSTANCE_H
#define CLASSIFICATION_INSTANCE_H

#include <ArrayList.h>
#include "../Attribute/Attribute.h"
#include "Vector.h"

struct instance{
    char* class_label;
    Array_list_ptr attributes;
};

typedef struct instance Instance;

typedef Instance *Instance_ptr;

Instance_ptr create_instance(const char* class_label, Array_list_ptr attributes);

Instance_ptr create_instance2(const char* class_label);

void free_instance(Instance_ptr instance);

void add_discrete_attribute(Instance_ptr instance, const char* value);

void add_continuous_attribute(Instance_ptr instance, double value);

void add_attribute_to_instance(Instance_ptr instance, Attribute_ptr attribute);

void add_vector_attribute(Instance_ptr instance, Vector_ptr vector);

void remove_attribute_from_instance(Instance_ptr instance, int index);

void remove_all_attributes_from_instance(Instance_ptr instance);

Attribute_ptr get_attribute(const Instance* instance, int index);

int attribute_size(const Instance* instance);

int instance_continuous_attribute_size(const Instance* instance);

Array_list_ptr instance_continuous_attributes(const Instance* instance);

Vector_ptr to_vector(const Instance* instance);

int compare_instance_labels(const Instance* instance1, const Instance* instance2);

#endif //CLASSIFICATION_INSTANCE_H
