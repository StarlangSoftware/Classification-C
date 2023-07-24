//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#ifndef CLASSIFICATION_ATTRIBUTE_H
#define CLASSIFICATION_ATTRIBUTE_H

#include <stdbool.h>
#include <ArrayList.h>
#include <StringUtils.h>
#include "AttributeType.h"

struct attribute{
    union{
        bool bool_value;
        int int_value;
        double float_value;
        char* string_value;
    };
    Attribute_type attribute_type;
    int max_index;
};

typedef struct attribute Attribute;

typedef Attribute* Attribute_ptr;

Attribute_ptr create_binary_attribute(bool value);

Attribute_ptr create_binary_attribute2(const char* value);

Attribute_ptr create_continuous_attribute(double value);

Attribute_ptr create_discrete_attribute(const char* value);

Attribute_ptr create_discrete_indexed_attribute(int index, int max_index);

Attribute_ptr clone_attribute(Attribute_ptr attribute);

void free_attribute(Attribute_ptr attribute);

int continuous_attribute_size(const Attribute* attribute);

Array_list_ptr continuous_attributes(const Attribute* attribute);

bool is_discrete(const Attribute* attribute);

bool is_continuous(const Attribute* attribute);

bool is_discrete_indexed(const Attribute* attribute);

bool is_binary(const Attribute* attribute);

#endif //CLASSIFICATION_ATTRIBUTE_H
