//
// Created by Olcay Taner YILDIZ on 24.07.2023.
//

#include <Memory/Memory.h>
#include "SubSetSelection.h"

/**
 * A constructor that sets the initial subset with given input.
 *
 * @param initial_sub_set FeatureSubSet input.
 */
Sub_set_selection_ptr create_sub_set_selection(Feature_sub_set_ptr initial_sub_set) {
    Sub_set_selection_ptr result = malloc_(sizeof(Sub_set_selection));
    result->initial_sub_set = initial_sub_set;
    return result;
}

/**
 * Constructor that creates a new feature subset and initializes indexList with given number of features.
 *
 * @param number_of_features Indicates the indices of indexList.
 */
Sub_set_selection_ptr create_sub_set_selection2(int number_of_features) {
    Sub_set_selection_ptr result = malloc_(sizeof(Sub_set_selection));
    result->initial_sub_set = create_feature_sub_set(number_of_features);
    return result;
}

/**
 * Constructor that creates a new feature subset selection.
 */
Sub_set_selection_ptr create_sub_set_selection3() {
    Sub_set_selection_ptr result = malloc_(sizeof(Sub_set_selection));
    result->initial_sub_set = create_feature_sub_set3();
    return result;
}

/**
 * Frees memory allocated for sub set selection.
 * @param sub_set_selection Current subset selection algorithm
 */
void free_sub_set_selection(Sub_set_selection_ptr sub_set_selection) {
    free_feature_sub_set(sub_set_selection->initial_sub_set);
    free_(sub_set_selection);
}

/**
 * The forward method starts with having no feature in the model. In each iteration, it keeps adding the features that are not currently listed.
 *
 * @param sub_set_selection Current subset selection algorithm
 * @param current_sub_set_list ArrayList to add the FeatureSubsets.
 * @param current           FeatureSubset that will be added to currentSubSetList.
 * @param number_of_features  The number of features to add the subset.
 */
void
forward(Sub_set_selection_ptr sub_set_selection, Array_list_ptr current_sub_set_list, const Feature_sub_set *current,
        int number_of_features) {
    for (int i = 0; i < number_of_features; i++){
        if (!contains_feature(current, i)){
            Feature_sub_set_ptr candidate = clone_feature_sub_set(current);
            add_feature(candidate, i);
            array_list_add(current_sub_set_list, candidate);
        }
    }
}

/**
 * The backward method starts with all the features and removes the least significant feature at each iteration.
 *
 * @param sub_set_selection Current subset selection algorithm
 * @param current_sub_set_list ArrayList to add the FeatureSubsets.
 * @param current           FeatureSubset that will be added to currentSubSetList
 */
void
backward(Sub_set_selection_ptr sub_set_selection, Array_list_ptr current_sub_set_list, const Feature_sub_set *current) {
    for (int i = 0; i < size_of_feature_sub_set(current); i++){
        Feature_sub_set_ptr candidate = clone_feature_sub_set(current);
        remove_feature(candidate, i);
        array_list_add(current_sub_set_list, candidate);
    }
}

/**
 * The operator method calls forward method which starts with having no feature in the model. In each iteration,
 * it keeps adding the features that are not currently listed.
 *
 * @param sub_set_selection Current subset selection algorithm
 * @param current          FeatureSubset that will be added to new ArrayList.
 * @param number_of_features Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSets created from backward.
 */
Array_list_ptr forward_selection(Sub_set_selection_ptr sub_set_selection, const Feature_sub_set *current, int number_of_features) {
    Array_list_ptr result = create_array_list();
    forward(sub_set_selection, result, current, number_of_features);
    return result;
}

/**
 * The operator method calls backward method which starts with all the features and removes the least significant feature at each iteration.
 *
 * @param sub_set_selection Current subset selection algorithm
 * @param current          FeatureSubset that will be added to new ArrayList.
 * @param number_of_features Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSets created from backward.
 */
Array_list_ptr
backward_selection(Sub_set_selection_ptr sub_set_selection, const Feature_sub_set *current, int number_of_features) {
    Array_list_ptr result = create_array_list();
    backward(sub_set_selection, result, current);
    return result;
}

/**
 * The operator method calls forward and backward methods.
 *
 * @param sub_set_selection Current subset selection algorithm
 * @param current          FeatureSubSet input.
 * @param number_of_features Indicates the indices of indexList.
 * @return ArrayList of FeatureSubSet.
 */
Array_list_ptr
floating_selection(Sub_set_selection_ptr sub_set_selection, const Feature_sub_set *current, int number_of_features) {
    Array_list_ptr result = create_array_list();
    forward(sub_set_selection, result, current, number_of_features);
    backward(sub_set_selection, result, current);
    return result;
}
