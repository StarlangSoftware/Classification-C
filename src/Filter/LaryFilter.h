//
// Created by Olcay Taner YILDIZ on 22.07.2023.
//

#ifndef CLASSIFICATION_LARYFILTER_H
#define CLASSIFICATION_LARYFILTER_H

#include "../DataSet/DataSet.h"

struct lary_filter{
    Data_set_ptr data_set;
    Array_list_ptr attribute_distributions;
};

typedef struct lary_filter Lary_filter;

typedef Lary_filter *Lary_filter_ptr;

Lary_filter_ptr create_lary_filter(Data_set_ptr data_set);

void free_lary_filter(Lary_filter_ptr lary_filter);

void remove_discrete_attributes_instance(Lary_filter_ptr lary_filter, Instance_ptr instance, int size);

void remove_discrete_attributes_definition(Lary_filter_ptr lary_filter, int size);

void convert_with_lary_filter(Lary_filter_ptr lary_filter, void* convert_instance(Lary_filter_ptr lary_filter, Instance_ptr instance), void* convert_data_definition(Lary_filter_ptr lary_filter));

#endif //CLASSIFICATION_LARYFILTER_H
