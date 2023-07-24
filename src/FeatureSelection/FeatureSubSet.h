//
// Created by Olcay Taner YILDIZ on 24.07.2023.
//

#ifndef CLASSIFICATION_FEATURESUBSET_H
#define CLASSIFICATION_FEATURESUBSET_H

#include <ArrayList.h>

struct feature_sub_set{
    Array_list_ptr index_list;
};

typedef struct feature_sub_set Feature_sub_set;

typedef Feature_sub_set *Feature_sub_set_ptr;

Feature_sub_set_ptr create_feature_sub_set(int number_of_features);

Feature_sub_set_ptr create_feature_sub_set2(Array_list_ptr index_list);

Feature_sub_set_ptr create_feature_sub_set3();

void free_feature_sub_set(Feature_sub_set_ptr feature_sub_set);

int size_of_feature_sub_set(const Feature_sub_set* feature_sub_set);

int get_feature(const Feature_sub_set* feature_sub_set, int index);

bool contains_feature(const Feature_sub_set* feature_sub_set, int feature_no);

void add_feature(Feature_sub_set_ptr feature_sub_set, int feature_no);

void remove_feature(Feature_sub_set_ptr feature_sub_set, int index);

Feature_sub_set_ptr clone_feature_sub_set(const Feature_sub_set* feature_sub_set);

#endif //CLASSIFICATION_FEATURESUBSET_H
