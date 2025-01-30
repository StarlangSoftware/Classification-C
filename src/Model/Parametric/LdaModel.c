//
// Created by Olcay Taner YILDIZ on 26.06.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include <Vector.h>
#include <float.h>
#include <Memory/Memory.h>
#include <math.h>
#include "LdaModel.h"
#include "../../InstanceList/Partition.h"

/**
 * A constructor which sets the priorDistribution, w and w1 according to given inputs.
 *
 * @param prior_distribution DiscreteDistribution input.
 * @param w                 HashMap of String and Vectors.
 * @param w0                HashMap of String and Double.
 */
Lda_model_ptr create_lda_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr w, Hash_map_ptr w0) {
    Lda_model_ptr result = malloc_(sizeof(Lda_model), "create_lda_model");
    result->prior_distribution = prior_distribution;
    result->w = w;
    result->w0 = w0;
    return result;
}

/**
 * Loads a Linear Discriminant Analysis model from an input model file.
 * @param file_name Model file name.
 */
Lda_model_ptr create_lda_model2(const char *file_name) {
    Lda_model_ptr result = malloc_(sizeof(Lda_model), "create_lda_model2");
    FILE* input_file = fopen(file_name, "r");
    result->w = create_string_hash_map();
    result->w0 = create_string_hash_map();
    result->prior_distribution = create_discrete_distribution2(input_file);
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        char class_label[MAX_LINE_LENGTH];
        double* weight = malloc_(sizeof(double), "create_lda_model2");
        fscanf(input_file, "%s %lf", class_label, weight);
        hash_map_insert(result->w0, class_label, weight);
    }
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        char class_label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", class_label);
        Vector_ptr vector = create_vector5(input_file);
        hash_map_insert(result->w, class_label, vector);
    }
    fclose(input_file);
    return result;
}

/**
 * The calculateMetric method takes an Instance and a String as inputs. It returns the dot product of given Instance
 * and w0 plus w1.
 *
 * @param instance Instance input.
 * @param C_i       String input.
 * @return The dot product of given Instance and w0 plus w1.
 */
double calculate_metric_lda(const Lda_model *lda_model, const Instance *instance, const char *C_i) {
    double w0i;
    Vector_ptr xi = to_vector(instance);
    Vector_ptr wi = hash_map_get(lda_model->w, C_i);
    w0i = *(double*)hash_map_get(lda_model->w0, C_i);
    double result = dot_product(wi, xi) + w0i;
    free_vector(xi);
    return result;
}

/**
 * Frees memory allocated for Lda model.
 * @param lda_model Lda model.
 */
void free_lda_model(Lda_model_ptr lda_model) {
    free_discrete_distribution(lda_model->prior_distribution);
    free_hash_map(lda_model->w, (void (*)(void *)) free_vector);
    free_hash_map(lda_model->w0, free_);
    free_(lda_model);
}

char *predict_lda(const void *model, const Instance *instance) {
    Lda_model_ptr lda_model = (Lda_model_ptr) model;
    double max_metric = -DBL_MAX;
    char* predicted_class = get_max_item(lda_model->prior_distribution);
    int size = size_of_distribution(lda_model->prior_distribution);
    Array_list_ptr possible_labels = get_items(lda_model->prior_distribution);
    for (int i = 0; i < size; i++){
        char* C_i = array_list_get(possible_labels, i);
        if (contains_distribution(lda_model->prior_distribution, C_i)){
            double metric = calculate_metric_lda(model, instance, C_i);
            if (metric > max_metric){
                max_metric = metric;
                predicted_class = C_i;
            }
        }
    }
    free_array_list(possible_labels, NULL);
    return predicted_class;
}

/**
 * Training algorithm for the linear discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter -
 */
Model_ptr train_lda(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_lda_1");
    Discrete_distribution_ptr priorDistribution = class_distribution(train_set);
    Partition_ptr class_lists = create_partition3(train_set);
    Hash_map_ptr w = create_string_hash_map();
    Hash_map_ptr w0 = create_string_hash_map();
    int size = instance_continuous_attribute_size(get_instance(train_set, 0));
    Matrix_ptr all_covariance = create_matrix(size, size);
    for (int i = 0; i < size_of_partition(class_lists); i++){
        Vector_ptr average_vector = create_vector(continuous_attribute_average2(get_instance_list(class_lists, i)));
        Matrix_ptr class_covariance = covariance(get_instance_list(class_lists, i), average_vector);
        multiply_with_constant(class_covariance, get_instance_list(class_lists, i)->list->size - 1);
        add_matrix(all_covariance, class_covariance);
        free_vector(average_vector);
        free_matrix(class_covariance);
    }
    divide_by_constant(all_covariance, size_of_instance_list(train_set) - size_of_partition(class_lists));
    inverse(all_covariance);
    for (int i = 0; i < size_of_partition(class_lists); i++) {
        Instance_list_ptr class_list = get_instance_list(class_lists, i);
        char* C_i = get_instance(class_list, 0)->class_label;
        Vector_ptr average_vector = create_vector(continuous_attribute_average2(class_list));
        Vector_ptr wi = multiply_with_vector_from_left(all_covariance, average_vector);
        hash_map_insert(w, C_i, wi);
        double* w0i = malloc_(sizeof(double), "train_lda_2");
        *w0i = -0.5 * dot_product(wi, average_vector) + log(get_probability(priorDistribution, C_i));
        hash_map_insert(w0, C_i, w0i);
        free_vector(average_vector);
    }
    free_matrix(all_covariance);
    free_partition(class_lists);
    result->model = create_lda_model(priorDistribution, w, w0);
    result->train = train_lda;
    result->predict = predict_lda;
    result->predict_probability = NULL;
    return result;
}

/**
 * Loads the Lda model from an input file.
 * @param file_name File name of the Lda model.
 */
Model_ptr load_lda(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_lda");
    result->model = create_lda_model2(file_name);
    result->train = train_lda;
    result->predict = predict_lda;
    result->predict_probability = NULL;
    return result;
}

/**
 * Frees memory allocated for Lda model.
 * @param lda Lda model.
 */
void free_lda(Model_ptr lda) {
    free_lda_model(lda->model);
    free_(lda);
}
