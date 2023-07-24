//
// Created by Olcay Taner YILDIZ on 24.07.2023.
//

#include <stdlib.h>
#include <HashMap/HashMap.h>
#include "FeatureSubSet.h"

/**
 * A constructor that takes number of features as input and initializes indexList with these numbers.
 *
 * @param numberOfFeatures Indicates the indices of indexList.
 */
Feature_sub_set_ptr create_feature_sub_set(int number_of_features) {
    Feature_sub_set_ptr result = malloc(sizeof(Feature_sub_set));
    result->index_list = create_array_list();
    for (int i = 0; i < number_of_features; i++){
        int* value = malloc(sizeof(int));
        *value = i;
        array_list_add(result->index_list, value);
    }
    return result;
}

/**
 * A constructor that sets the indexList {@link vector}.
 *
 * @param indexList A vector consists of integer indices.
 */
Feature_sub_set_ptr create_feature_sub_set2(Array_list_ptr index_list) {
    Feature_sub_set_ptr result = malloc(sizeof(Feature_sub_set));
    result->index_list = index_list;
    return result;
}

/**
 * A constructor that creates a new vector for indexList.
 */
Feature_sub_set_ptr create_feature_sub_set3() {
    Feature_sub_set_ptr result = malloc(sizeof(Feature_sub_set));
    result->index_list = create_array_list();
    return result;
}

/**
 * The size method returns the size of the indexList.
 *
 * @return The size of the indexList.
 */
int size_of_feature_sub_set(const Feature_sub_set* feature_sub_set) {
    return feature_sub_set->index_list->size;
}

/**
 * The get method returns the item of indexList at given index.
 *
 * @param index Index of the indexList to be accessed.
 * @return The item of indexList at given index.
 */
int get_feature(const Feature_sub_set* feature_sub_set, int index) {
    return *(int*)array_list_get(feature_sub_set->index_list, index);
}

/**
 * The contains method returns True, if indexList contains given input number and False otherwise.
 *
 * @param featureNo Feature number that will be checked.
 * @return True, if indexList contains given input number.
 */
bool contains_feature(const Feature_sub_set* feature_sub_set, int feature_no) {
    return array_list_contains(feature_sub_set->index_list, &feature_no,
                               (int (*)(const void *, const void *)) compare_int);
}

void free_feature_sub_set(Feature_sub_set_ptr feature_sub_set) {
    free_array_list(feature_sub_set->index_list, free);
    free(feature_sub_set);
}

/**
 * The add method adds given Integer to the indexList.
 *
 * @param featureNo Integer that will be added to indexList.
 */
void add_feature(Feature_sub_set_ptr feature_sub_set, int feature_no) {
    int* value = malloc(sizeof(int));
    *value = feature_no;
    array_list_add(feature_sub_set->index_list, value);
}

/**
 * The remove method removes the item of indexList at the given index.
 *
 * @param index Index of the item that will be removed.
 */
void remove_feature(Feature_sub_set_ptr feature_sub_set, int index) {
    array_list_remove(feature_sub_set->index_list, index, free);
}

/**
 * The clone method creates a new vector with the elements of indexList and returns it as a new FeatureSubSet.
 *
 * @return A new vector with the elements of indexList and returns it as a new FeatureSubSet.
 */
Feature_sub_set_ptr clone_feature_sub_set(const Feature_sub_set *feature_sub_set) {
    Array_list_ptr new_index_list = create_array_list();
    array_list_add_all(new_index_list, feature_sub_set->index_list);
    return create_feature_sub_set2(new_index_list);
}
