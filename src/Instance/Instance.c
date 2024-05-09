//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#include <StringUtils.h>
#include <HashMap/HashMap.h>
#include <Memory/Memory.h>
#include "Instance.h"

/**
 * Constructor for a single instance. Given the attributes and class label, it generates a new instance.
 *
 * @param class_label Class label of the instance.
 * @param attributes Attributes of the instance.
 */
Instance_ptr create_instance(const char *class_label, Array_list_ptr attributes) {
    Instance_ptr result = malloc_(sizeof(Instance), "create_instance");
    result->class_label = str_copy(result->class_label, class_label);
    result->attributes = attributes;
    return result;
}

/**
 * Frees memory allocated for the instance
 * @param instance Instance
 */
void free_instance(Instance_ptr instance) {
    free_(instance->class_label);
    free_array_list(instance->attributes, (void (*)(void *)) free_attribute);
    free_(instance);
}

/**
 * Constructor for a single instance. Given the class label, it generates a new instance with 0 attributes.
 * Attributes must be added later with different addAttribute methods.
 *
 * @param class_label Class label of the instance.
 */
Instance_ptr create_instance2(const char *class_label) {
    Instance_ptr result = malloc_(sizeof(Instance), "create_instance2");
    result->class_label = str_copy(result->class_label, class_label);
    result->attributes = create_array_list();
    return result;
}

/**
 * Adds a discrete attribute with the given String value.
 *
 * @param value Value of the discrete attribute.
 */
void add_discrete_attribute(Instance_ptr instance, const char *value) {
    array_list_add(instance->attributes, create_discrete_attribute(value));
}

/**
 * Adds a continuous attribute with the given double value.
 *
 * @param value Value of the continuous attribute.
 */
void add_continuous_attribute(Instance_ptr instance, double value) {
    array_list_add(instance->attributes, create_continuous_attribute(value));
}

/**
 * Adds a new attribute.
 *
 * @param attribute Attribute to be added.
 */
void add_attribute_to_instance(Instance_ptr instance, Attribute_ptr attribute) {
    array_list_add(instance->attributes, attribute);
}

/**
 * Adds a Vector of continuous attributes.
 *
 * @param vector Vector that has the continuous attributes.
 */
void add_vector_attribute(Instance_ptr instance, Vector_ptr vector) {
    for (int i = 0; i < vector->size; i++) {
        array_list_add(instance->attributes, create_continuous_attribute(get_value(vector, i)));
    }
}

/**
 * Removes attribute with the given index from the attributes list.
 *
 * @param index Index of the attribute to be removed.
 */
void remove_attribute_from_instance(Instance_ptr instance, int index) {
    array_list_remove(instance->attributes, index, (void (*)(void *)) free_attribute);
}

/**
 * Removes all the attributes from the attributes list.
 */
void remove_all_attributes_from_instance(Instance_ptr instance) {
    array_list_clear(instance->attributes, (void (*)(void *)) free_attribute);
}

/**
 * Accessor for a single attribute.
 *
 * @param index Index of the attribute to be accessed.
 * @return Attribute with index 'index'.
 */
Attribute_ptr get_attribute(const Instance* instance, int index) {
    return array_list_get(instance->attributes, index);
}

/**
 * Returns the number of attributes in the attributes list.
 *
 * @return Number of attributes in the attributes list.
 */
int attribute_size(const Instance* instance) {
    return instance->attributes->size;
}

/**
 * Returns the number of continuous and discrete indexed attributes in the attributes list.
 *
 * @return Number of continuous and discrete indexed attributes in the attributes list.
 */
int instance_continuous_attribute_size(const Instance* instance) {
    int size = 0;
    for (int i = 0; i < instance->attributes->size; i++) {
        size += continuous_attribute_size(array_list_get(instance->attributes, i));
    }
    return size;
}

/**
 * The continuousAttributes method creates a new vector result and it adds the continuous attributes of the
 * attributes list and also it adds 1 for the discrete indexed attributes
 *
 * @return result vector that has continuous and discrete indexed attributes.
 */
Array_list_ptr instance_continuous_attributes(const Instance* instance) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < instance->attributes->size; i++) {
        Array_list_ptr inserted = continuous_attributes(array_list_get(instance->attributes, i));
        array_list_add_all(result, inserted);
        free_array_list(inserted, NULL);
    }
    return result;
}

/**
 * The toVector method returns a Vector of continuous attributes and discrete indexed attributes.
 *
 * @return Vector of continuous attributes and discrete indexed attributes.
 */
Vector_ptr to_vector(const Instance* instance) {
    Array_list_ptr values = create_array_list();
    for (int i = 0; i < instance->attributes->size; i++) {
        Array_list_ptr inserted = continuous_attributes(array_list_get(instance->attributes, i));
        array_list_add_all(values, inserted);
        free_array_list(inserted, NULL);
    }
    return create_vector(values);
}

/**
 * Compares two Instance inputs and returns a positive value if the first input's class label is greater
 * than the second's class label input lexicographically.
 *
 * @param o1 First Instance to be compared.
 * @param o2 Second Instance to be compared.
 * @return Negative value if the class label of the first instance is less than the class label of the second instance.
 * Positive value if the class label of the first instance is greater than the class label of the second instance.
 * 0 if the class label of the first instance is equal to the class label of the second instance.
 */
int compare_instance_labels(const Instance *instance1, const Instance *instance2) {
    return compare_string(instance1->class_label, instance2->class_label);
}

/**
* Compares two instance on the values of the attribute with index attributeIndex.
*
* @param instance1 First instance to be compared
* @param instance2 Second instance to be compared
* @return -1 if the attribute value of the first instance is less than the attribute value of the second instance.
* 1 if the attribute value of the first instance is greater than the attribute value of the second instance.
* 0 if the attribute value of the first instance is equal to the attribute value of the second instance.
*/
int compare_attributes(const Instance *instance1, const Instance *instance2, const void *arg) {
    double value1 = get_attribute(instance1, *(int *)arg)->float_value;
    double value2 = get_attribute(instance2, *(int *)arg)->float_value;
    if (value1 < value2){
        return -1;
    } else {
        if (value1 > value2) {
            return 1;
        } else {
            return 0;
        }
    }
}

/**
 * The getSubSetOfFeatures method takes a FeatureSubSet as an input. First it creates a result Instance
 * with the class label, and adds the attributes of the given featureSubSet to it.
 *
 * @param featureSubSet FeatureSubSet an vector of indices.
 * @return result Instance.
 */
Instance_ptr get_sub_set_of_features_instance(const Instance *instance, const Feature_sub_set *feature_sub_set) {
    Instance_ptr result = create_instance2(instance->class_label);
    for (int i = 0; i < size_of_feature_sub_set(feature_sub_set); i++){
        Attribute_ptr attribute = get_attribute(instance, get_feature(feature_sub_set, i));
        add_attribute_to_instance(result, clone_attribute(attribute));
    }
    return result;
}
