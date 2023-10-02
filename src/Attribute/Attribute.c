//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#include <stdlib.h>
#include <string.h>
#include "Attribute.h"

/**
 * Constructor for a binary discrete attribute. The attribute can take only two values "True" or "False".
 *
 * @param value Value of the attribute. Can be true or false.
 */
Attribute_ptr create_binary_attribute(bool value) {
    Attribute_ptr result = malloc(sizeof(Attribute));
    result->attribute_type = BINARY;
    result->bool_value = value;
    return result;
}

Attribute_ptr create_binary_attribute2(const char *value) {
    Attribute_ptr result = malloc(sizeof(Attribute));
    result->attribute_type = BINARY;
    if (strcmp(value, "true") == 0 || strcmp(value, "True") == 0 || strcmp(value, "TRUE") == 0){
        result->bool_value = true;
    } else {
        if (strcmp(value, "false") == 0 || strcmp(value, "False") == 0 || strcmp(value, "FALSE") == 0){
            result->bool_value = false;
        } else {
            result->bool_value = false;
        }
    }
    return result;
}

/**
 * Constructor for a continuous attribute.
 *
 * @param value Value of the attribute.
 */
Attribute_ptr create_continuous_attribute(double value) {
    Attribute_ptr result = malloc(sizeof(Attribute));
    result->attribute_type = CONTINUOUS;
    result->float_value = value;
    return result;
}

/**
 * Constructor for a discrete attribute.
 *
 * @param value Value of the attribute.
 * @param index Index of the attribute.
 * @param maxIndex Maximum index of the attribute.
 */
Attribute_ptr create_discrete_indexed_attribute(int index, int max_index) {
    Attribute_ptr result = malloc(sizeof(Attribute));
    result->attribute_type = DISCRETE_INDEXED;
    result->int_value = index;
    result->max_index = max_index;
    return result;
}

Attribute_ptr create_discrete_attribute(const char *value) {
    Attribute_ptr result = malloc(sizeof(Attribute));
    result->attribute_type = DISCRETE;
    result->string_value = str_copy(result->string_value, value);
    return result;
}

int continuous_attribute_size(const Attribute *attribute) {
    switch (attribute->attribute_type) {
        case CONTINUOUS:
            return 1;
        case DISCRETE:
        case BINARY:
            return 0;
        case DISCRETE_INDEXED:
            return attribute->max_index;
    }
}

Array_list_ptr continuous_attributes(const Attribute *attribute) {
    Array_list_ptr result = create_array_list();
    switch (attribute->attribute_type) {
        case CONTINUOUS:
            array_list_add_double(result, attribute->float_value);
            break;
        case DISCRETE:
        case BINARY:
            break;
        case DISCRETE_INDEXED:
            for (int i = 0; i < attribute->max_index; i++) {
                if (i != attribute->int_value) {
                    array_list_add_double(result, 0.0);
                } else {
                    array_list_add_double(result, 1.0);
                }
            }
            break;
    }
    return result;
}

void free_attribute(Attribute_ptr attribute) {
    if (attribute->attribute_type == DISCRETE){
        free(attribute->string_value);
    }
    free(attribute);
}

bool is_discrete(const Attribute *attribute) {
    return attribute->attribute_type == DISCRETE;
}

bool is_continuous(const Attribute *attribute) {
    return attribute->attribute_type == CONTINUOUS;
}

bool is_discrete_indexed(const Attribute *attribute) {
    return attribute->attribute_type == DISCRETE_INDEXED;
}

bool is_binary(const Attribute *attribute) {
    return attribute->attribute_type == BINARY;
}

Attribute_ptr clone_attribute(Attribute_ptr attribute) {
    switch (attribute->attribute_type) {
        case BINARY:
            return create_binary_attribute(attribute->bool_value);
        case CONTINUOUS:
            return create_continuous_attribute(attribute->float_value);
        case DISCRETE:
            return create_discrete_attribute(attribute->string_value);
        case DISCRETE_INDEXED:
            return create_discrete_indexed_attribute(attribute->int_value, attribute->max_index);
    }
}
