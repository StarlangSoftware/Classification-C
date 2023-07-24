//
// Created by Olcay Taner YILDIZ on 24.07.2023.
//

#ifndef CLASSIFICATION_SUBSETSELECTION_H
#define CLASSIFICATION_SUBSETSELECTION_H

#include "FeatureSubSet.h"

struct sub_set_selection{
    Feature_sub_set_ptr initial_sub_set;
};

typedef struct sub_set_selection Sub_set_selection;

typedef Sub_set_selection *Sub_set_selection_ptr;

Sub_set_selection_ptr create_sub_set_selection(Feature_sub_set_ptr initial_sub_set);

Sub_set_selection_ptr create_sub_set_selection2(int number_of_features);

Sub_set_selection_ptr create_sub_set_selection3();

void free_sub_set_selection(Sub_set_selection_ptr sub_set_selection);

void forward(Sub_set_selection_ptr sub_set_selection, Array_list_ptr current_sub_set_list, const Feature_sub_set* current, int number_of_features);

void backward(Sub_set_selection_ptr sub_set_selection, Array_list_ptr current_sub_set_list, const Feature_sub_set* current);

Array_list_ptr forward_selection(Sub_set_selection_ptr sub_set_selection, const Feature_sub_set *current, int number_of_features);

Array_list_ptr backward_selection(Sub_set_selection_ptr sub_set_selection, const Feature_sub_set *current, int number_of_features);

Array_list_ptr floating_selection(Sub_set_selection_ptr sub_set_selection, const Feature_sub_set *current, int number_of_features);

#endif //CLASSIFICATION_SUBSETSELECTION_H
