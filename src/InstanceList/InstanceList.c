//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include <FileUtils.h>
#include <string.h>
#include <HashMap/HashMap.h>
#include <math.h>
#include "InstanceList.h"
#include "../Instance/Instance.h"
#include "Dictionary/Word.h"
#include "../Classifier/Classifier.h"

/**
 * Empty constructor for an instance list. Initializes the instance list with zero instances.
 */
Instance_list_ptr create_instance_list() {
    Instance_list_ptr result = malloc(sizeof(Instance_list));
    result->list =  create_array_list();
    return result;
}

void free_instance_list(Instance_list_ptr instance_list) {
    free_array_list(instance_list->list, (void (*)(void *)) free_instance);
    free(instance_list);
}

/**
 * Constructor for an instance list with a given data definition, data file and a separator character. Each instance
 * must be stored in a separate line separated with the character separator. The last item must be the class label.
 * The function reads the file line by line and for each line; depending on the data definition, that is, type of
 * the attributes, adds discrete and continuous attributes to a new instance. For example, given the data set file
 * <p>
 * red;1;0.4;true
 * green;-1;0.8;true
 * blue;3;1.3;false
 * <p>
 * where the first attribute is a discrete attribute, second and third attributes are continuous attributes, the
 * fourth item is the class label.
 *
 * @param definition Data definition of the data set.
 * @param separator  Separator character which separates the attribute values in the data file.
 * @param fileName   Name of the data set file.
 */
Instance_list_ptr
create_instance_list2(const Data_definition *definition, const char *separators, const char *file_name) {
    FILE* input_file;
    char line[MAX_LINE_LENGTH];
    Instance_list_ptr result = malloc(sizeof(Instance_list));
    result->list =  create_array_list();
    input_file = fopen(file_name, "r");
    char* input = fgets(line, MAX_LINE_LENGTH, input_file);
    while (input != NULL){
        line[strcspn(line, "\n")] = 0;
        Array_list_ptr attribute_list = split_with_char(line, separators);
        if (attribute_list->size == attribute_count(definition) + 1){
            String_ptr attribute = array_list_get(attribute_list, attribute_list->size - 1);
            Instance_ptr current = create_instance2(attribute->s);
            for (int i = 0; i < attribute_list->size - 1; i++){
                attribute = array_list_get(attribute_list, i);
                switch (get_attribute_type(definition, i)) {
                    case DISCRETE:
                        add_attribute_to_instance(current, create_discrete_attribute(attribute->s));
                        break;
                    case BINARY:
                        add_attribute_to_instance(current, create_binary_attribute2(attribute->s));
                        break;
                    case CONTINUOUS:
                        add_attribute_to_instance(current, create_continuous_attribute(atof(attribute->s)));
                        break;
                    case DISCRETE_INDEXED:
                        add_attribute_to_instance(current, create_discrete_indexed_attribute(feature_value_index(definition, i, attribute->s),
                                                                                             number_of_values(definition, i)));
                        break;
                }
            }
            array_list_add(result->list, current);
        }
        input = fgets(line, MAX_LINE_LENGTH, input_file);
    }
    fclose(input_file);

    return result;
}

/**
 * Mutator for the list variable.
 *
 * @param list New list for the list variable.
 */
Instance_list_ptr create_instance_list3(Array_list_ptr list) {
    Instance_list_ptr result = malloc(sizeof(Instance_list));
    result->list =  list;
    return result;
}

/**
 * Adds instance to the instance list.
 *
 * @param instance Instance to be added.
 */
void add_instance(Instance_list_ptr instance_list, Instance_ptr instance) {
    array_list_add(instance_list->list, instance);
}

/**
 * Adds a list of instances to the current instance list.
 *
 * @param instanceList List of instances to be added.
 */
void add_all_instances(Instance_list_ptr instance_list, const Array_list* instances_added) {
    array_list_add_all(instance_list->list, instances_added);
}

/**
 * Returns size of the instance list.
 *
 * @return Size of the instance list.
 */
int size_of_instance_list(const Instance_list* instance_list) {
    return instance_list->list->size;
}

/**
 * Accessor for a single instance with the given index.
 *
 * @param index Index of the instance.
 * @return Instance with index 'index'.
 */
Instance_ptr get_instance(const Instance_list *instance_list, int index) {
    return array_list_get(instance_list->list, index);
}

void sort_wrt_class_labels(Instance_list_ptr instance_list) {
    array_list_quick_sort(instance_list->list, (int (*)(const void *, const void *)) compare_instance_labels);
}

/**
 * Sorts attribute list according to the attribute with index 'attributeIndex'.
 *
 * @param attributeIndex index of the attribute.
 */
void sort_wrt_attribute_index(Instance_list_ptr instance_list, int attribute_index) {
    array_list_quick_sort2(instance_list->list, (int (*)(const void *, const void *, const void *)) compare_attributes, &attribute_index);
}

/**
 * Shuffles the instance list.
 * @param seed Seed is used for random number generation.
 */
void shuffle_instance_list(Instance_list_ptr instance_list, int seed) {
    array_list_shuffle(instance_list->list, seed);
}

/**
 * Creates a bootstrap sample from the current instance list.
 *
 * @param seed To create a different bootstrap sample, we need a new seed for each sample.
 * @return Bootstrap sample.
 */
Bootstrap_ptr bootstrap_instance_list(Instance_list_ptr instance_list, int seed) {
    return create_bootstrap(instance_list->list, seed);
}

/**
 * Extracts the class labels of each instance in the instance list and returns them in an array of {@link String}.
 *
 * @return A {@link vector} of class labels.
 */
Array_list_ptr get_class_labels(const Instance_list *instance_list) {
    Array_list_ptr class_labels = create_array_list();
    for (int i = 0; i < instance_list->list->size; i++){
        Instance_ptr instance = get_instance(instance_list, i);
        array_list_add(class_labels, instance->class_label);
    }
    return class_labels;
}

/**
 * Extracts the class labels of each instance in the instance list and returns them as a set.
 *
 * @return A {@link vector} of distinct class labels.
 */
Array_list_ptr get_distinct_class_labels(const Instance_list *instance_list) {
    Array_list_ptr class_labels = create_array_list();
    for (int i = 0; i < instance_list->list->size; i++){
        Instance_ptr instance = get_instance(instance_list, i);
        if (!array_list_contains(class_labels, instance->class_label,
                                (int (*)(const void *, const void *)) compare_string)){

            array_list_add(class_labels, instance->class_label);
        }
    }
    return class_labels;
}

/**
 * Accessor for the instances.
 *
 * @return Instances.
 */
Array_list_ptr get_instances(Instance_list_ptr instance_list) {
    return instance_list->list;
}

/**
 * Extracts distinct discrete values of a given attribute as an array of strings.
 *
 * @param attributeIndex Index of the discrete attribute.
 * @return An array of distinct values of a discrete attribute.
 */
Array_list_ptr get_attribute_value_list(const Instance_list* instance_list, int attribute_index) {
    Array_list_ptr value_list = create_array_list();
    for (int i = 0; i < instance_list->list->size; i++){
        Instance_ptr instance = get_instance(instance_list, i);
        Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
        if (!array_list_contains(value_list, attribute->string_value,
                                 (int (*)(const void *, const void *)) compare_string)){
            array_list_add(value_list, attribute->string_value);
        }
    }
    return value_list;
}

/**
 * Calculates the mean of a single attribute for this instance list (m_i). If the attribute is discrete, the maximum
 * occurring value for that attribute is returned. If the attribute is continuous, the mean value of the values of
 * all instances are returned.
 *
 * @param index Index of the attribute.
 * @return The mean value of the instances as an attribute.
 */
Attribute_ptr attribute_average(const Instance_list *instance_list, int attribute_index) {
    Instance_ptr instance = get_instance(instance_list, 0);
    Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
    if (attribute->attribute_type == CONTINUOUS){
        double sum = 0.0;
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            sum += attribute->float_value;
        }
        return create_continuous_attribute(sum / size_of_instance_list(instance_list));
    } else {
        Array_list_ptr values = create_array_list();
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            array_list_add(values, attribute->string_value);
        }
        attribute = create_discrete_attribute(get_maximum(values));
        free_array_list(values, NULL);
        return attribute;
    }
}

/**
 * Calculates the mean of a single attribute for this instance list (m_i).
 *
 * @param index Index of the attribute.
 * @return The mean value of the instances as an attribute.
 */
Array_list_ptr continuous_attribute_average(const Instance_list *instance_list, int attribute_index) {
    double *value;
    Instance_ptr instance = get_instance(instance_list, 0);
    Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
    if (attribute->attribute_type == DISCRETE_INDEXED){
        int max_index_size = attribute->max_index;
        Array_list_ptr values = create_array_list_of_double(max_index_size);
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            int value_index = attribute->int_value;
            value = array_list_get(values, value_index);
            (*value)++;
        }
        for (int i = 0; i < max_index_size; i++){
            value = array_list_get(values, i);
            (*value) /= instance_list->list->size;
        }
        return values;
    } else {
        if (attribute->attribute_type == CONTINUOUS){
            double sum = 0.0;
            for (int i = 0; i < instance_list->list->size; i++) {
                instance = get_instance(instance_list, i);
                attribute = array_list_get(instance->attributes, attribute_index);
                sum += attribute->float_value;
            }
            Array_list_ptr values = create_array_list();
            array_list_add_double(values, sum / instance_list->list->size);
            return values;
        } else {
            return NULL;
        }
    }
}

/**
 * Calculates the standard deviation of a single attribute for this instance list (m_i). If the attribute is discrete,
 * null returned. If the attribute is continuous, the standard deviation  of the values all instances are returned.
 *
 * @param index Index of the attribute.
 * @return The standard deviation of the instances as an attribute.
 */
Attribute_ptr attribute_standard_deviation(const Instance_list *instance_list, int attribute_index) {
    Instance_ptr instance = get_instance(instance_list, 0);
    Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
    if (attribute->attribute_type == CONTINUOUS){
        double average, sum = 0.0;
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            sum += attribute->float_value;
        }
        average = sum / instance_list->list->size;
        sum = 0.0;
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            sum += pow(attribute->float_value - average, 2);
        }
        return create_continuous_attribute(sqrt(sum / (instance_list->list->size - 1)));
    } else {
        return NULL;
    }
}

/**
 * Calculates the standard deviation of a single continuous attribute for this instance list (m_i).
 *
 * @param index Index of the attribute.
 * @return The standard deviation of the instances as an attribute.
 */
Array_list_ptr continuous_attribute_standard_deviation(const Instance_list *instance_list, int attribute_index) {
    double *value, *average;
    Instance_ptr instance = get_instance(instance_list, 0);
    Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
    if (attribute->attribute_type == DISCRETE_INDEXED){
        int max_index_size = attribute->max_index;
        Array_list_ptr averages = create_array_list_of_double(max_index_size);
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            int value_index = attribute->int_value;
            average = array_list_get(averages, value_index);
            (*average)++;
        }
        for (int i = 0; i < max_index_size; i++){
            average = array_list_get(averages, i);
            (*average) /= instance_list->list->size;
        }
        Array_list_ptr values = create_array_list_of_double(max_index_size);
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            int value_index = attribute->int_value;
            for (int j = 0; j < max_index_size; j++){
                value = array_list_get(values, j);
                average = array_list_get(averages, j);
                if (j == value_index){
                    (*value) += pow(1 - *average, 2);
                } else {
                    (*value) += pow(*average, 2);
                }
            }
        }
        free_array_list(averages, free);
        for (int i = 0; i < max_index_size; i++){
            value = array_list_get(values, i);
            (*value) = sqrt((*value) / (instance_list->list->size - 1));
        }
        return values;
    } else {
        if (attribute->attribute_type == CONTINUOUS){
            double avg, sum = 0.0;
            for (int i = 0; i < instance_list->list->size; i++) {
                instance = get_instance(instance_list, i);
                attribute = array_list_get(instance->attributes, attribute_index);
                sum += attribute->float_value;
            }
            avg = sum / instance_list->list->size;
            for (int i = 0; i < instance_list->list->size; i++) {
                instance = get_instance(instance_list, i);
                attribute = array_list_get(instance->attributes, attribute_index);
                sum += pow(attribute->float_value - avg, 2);
            }
            Array_list_ptr values = create_array_list();
            array_list_add_double(values, sqrt(sum / (instance_list->list->size - 1)));
            return values;
        } else {
            return NULL;
        }
    }
}

/**
 * The attributeDistribution method takes an index as an input and if the attribute of the instance at given index is
 * discrete, it returns the distribution of the attributes of that instance.
 *
 * @param index Index of the attribute.
 * @return Distribution of the attribute.
 */
Discrete_distribution_ptr attribute_distribution(const Instance_list *instance_list, int attribute_index) {
    Discrete_distribution_ptr distribution = create_discrete_distribution();
    Instance_ptr instance = get_instance(instance_list, 0);
    Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
    if (attribute->attribute_type == DISCRETE) {
        for (int i = 0; i < instance_list->list->size; i++) {
            instance = get_instance(instance_list, i);
            attribute = array_list_get(instance->attributes, attribute_index);
            add_item(distribution, attribute->string_value);
        }
    }
    return distribution;
}

/**
 * The attributeClassDistribution method takes an attribute index as an input. It loops through the instances, gets
 * the corresponding value of given attribute index and adds the class label of that instance to the discrete distributions list.
 *
 * @param attributeIndex Index of the attribute.
 * @return Distribution of the class labels.
 */
Array_list_ptr attribute_class_distribution(const Instance_list *instance_list, int attribute_index) {
    Array_list_ptr value_list = get_attribute_value_list(instance_list, attribute_index);
    Array_list_ptr distributions = create_array_list();
    for (int i = 0; i < value_list->size; i++){
        array_list_add(distributions, create_discrete_distribution());
    }
    for (int i = 0; i < instance_list->list->size; i++) {
        Instance_ptr instance = get_instance(instance_list, i);
        Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
        int index = array_list_index_of(value_list, attribute->string_value, (int (*)(const void *, const void *)) compare_string);
        Discrete_distribution_ptr distribution = array_list_get(distributions, index);
        add_item(distribution, instance->class_label);
    }
    return distributions;
}

/**
 * The discreteIndexedAttributeClassDistribution method takes an attribute index and an attribute value as inputs.
 * It loops through the instances, gets the corresponding value of given attribute index and given attribute value.
 * Then, adds the class label of that instance to the discrete indexed distributions list.
 *
 * @param attributeIndex Index of the attribute.
 * @param attributeValue Value of the attribute.
 * @return Distribution of the class labels.
 */
Discrete_distribution_ptr
discrete_indexed_attribute_class_distribution(const Instance_list *instance_list, int attribute_index,
                                              int attribute_value) {
    Discrete_distribution_ptr distribution = create_discrete_distribution();
    for (int i = 0; i < instance_list->list->size; i++) {
        Instance_ptr instance = get_instance(instance_list, i);
        Attribute_ptr attribute = array_list_get(instance->attributes, attribute_index);
        if (attribute->int_value == attribute_value){
            add_item(distribution, instance->class_label);
        }
    }
    return distribution;
}

/**
 * The classDistribution method returns the distribution of all the class labels of instances.
 *
 * @return Distribution of the class labels.
 */
Discrete_distribution_ptr class_distribution(const Instance_list *instance_list) {
    Discrete_distribution_ptr distribution = create_discrete_distribution();
    for (int i = 0; i < instance_list->list->size; i++) {
        Instance_ptr instance = get_instance(instance_list, i);
        add_item(distribution, instance->class_label);
    }
    return distribution;
}

/**
 * The allAttributesDistribution method returns the distributions of all the attributes of instances.
 *
 * @return Distributions of all the attributes of instances.
 */
Array_list_ptr all_attributes_distribution(const Instance_list *instance_list) {
    Array_list_ptr distributions = create_array_list();
    for (int i = 0; i < attribute_size(get_instance(instance_list, 0)); i++){
        array_list_add(distributions, attribute_distribution(instance_list, i));
    }
    return distributions;
}

/**
 * Returns the mean of all the attributes for instances in the list.
 *
 * @return Mean of all the attributes for instances in the list.
 */
Instance_ptr average(const Instance_list *instance_list) {
    Instance_ptr result = create_instance2(get_instance(instance_list, 0)->class_label);
    for (int i = 0; i < attribute_size(get_instance(instance_list, 0)); i++){
        add_attribute_to_instance(result, attribute_average(instance_list, i));
    }
    return result;
}

/**
 * Calculates mean of the attributes of instances.
 *
 * @return Mean of the attributes of instances.
 */
Array_list_ptr continuous_attribute_average2(const Instance_list *instance_list) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < attribute_size(get_instance(instance_list, 0)); i++){
        Array_list_ptr added = continuous_attribute_average(instance_list, i);
        array_list_add_all(result, added);
    }
    return result;
}

/**
 * Returns the standard deviation of attributes for instances.
 *
 * @return Standard deviation of attributes for instances.
 */
Instance_ptr standard_deviation(const Instance_list *instance_list) {
    Instance_ptr result = create_instance2(get_instance(instance_list, 0)->class_label);
    for (int i = 0; i < attribute_size(get_instance(instance_list, 0)); i++){
        add_attribute_to_instance(result, attribute_standard_deviation(instance_list, i));
    }
    return result;
}

/**
 * Returns the standard deviation of continuous attributes for instances.
 *
 * @return Standard deviation of continuous attributes for instances.
 */
Array_list_ptr continuous_attribute_standard_deviation2(const Instance_list *instance_list) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < attribute_size(get_instance(instance_list, 0)); i++){
        Array_list_ptr added = continuous_attribute_standard_deviation(instance_list, i);
        array_list_add_all(result, added);
    }
    return result;
}

/**
 * Calculates a covariance {@link Matrix} by using an average {@link Vector}.
 *
 * @param average Vector input.
 * @return Covariance {@link Matrix}.
 */
Matrix_ptr covariance(const Instance_list *instance_list, const Vector* average) {
    double mi, mj, xi, xj;
    Matrix_ptr result = create_matrix(instance_continuous_attribute_size(get_instance(instance_list, 0)), instance_continuous_attribute_size(get_instance(instance_list, 0)));
    for (int k = 0; k < instance_list->list->size; k++) {
        Instance_ptr instance = get_instance(instance_list, k);
        Array_list_ptr continuous_attributes = instance_continuous_attributes(instance);
        for (int i = 0; i < instance_continuous_attribute_size(instance); i++){
            xi = *(double*) array_list_get(continuous_attributes, i);
            mi = get_value(average, i);
            for (int j = 0; j < instance_continuous_attribute_size(instance); j++){
                xj = *(double*) array_list_get(continuous_attributes, j);
                mj = get_value(average, j);
                add_value_to_matrix(result, i, j, (xi - mi) * (xj - mj));
            }
        }
    }
    divide_by_constant(result, instance_list->list->size - 1);
    return result;
}

void clear(Instance_list_ptr instance_list) {
    array_list_clear(instance_list->list, (void (*)(void *)) free_instance);
}

Instance_list_ptr create_instance_list4(FILE *input_file) {
    char line[MAX_LINE_LENGTH];
    Instance_list_ptr result = malloc(sizeof(Instance_list));
    result->list =  create_array_list();
    fgets(line, MAX_LINE_LENGTH, input_file);
    line[strcspn(line, "\n")] = 0;
    Array_list_ptr attribute_types = split(line);
    int size;
    fscanf(input_file, "%d", &size);
    for (int i = 0; i < size; i++){
        fgets(line, MAX_LINE_LENGTH, input_file);
        line[strcspn(line, "\n")] = 0;
        Array_list_ptr attribute_list = create_array_list();
        Array_list_ptr attribute_values = str_split(line, ',');
        for (int j = 0; j < attribute_types->size; j++){
            String_ptr attribute_type = array_list_get(attribute_types, j);
            String_ptr attribute_value = array_list_get(attribute_values, j);
            if (string_equals2(attribute_type, "DISCRETE")){
                array_list_add(attribute_list, create_discrete_attribute(attribute_value->s));
            } else {
                if (string_equals2(attribute_type, "CONTINUOUS")){
                    array_list_add(attribute_list, create_continuous_attribute(atof(attribute_value->s)));
                }
            }
        }
        String_ptr class_label = array_list_get(attribute_values, attribute_types->size);
        Instance_ptr current = create_instance(class_label->s, attribute_list);
        array_list_add(result->list, current);
    }
    return result;
}

