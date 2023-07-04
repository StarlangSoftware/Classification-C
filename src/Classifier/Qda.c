//
// Created by Olcay Taner YILDIZ on 2.07.2023.
//

#include <stdlib.h>
#include <math.h>
#include "Qda.h"
#include "../InstanceList/Partition.h"
#include "../Model/QdaModel.h"

/**
 * Training algorithm for the quadratic discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
Classifier_ptr train_qda(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    Partition_ptr class_lists = create_partition3(train_set);
    Discrete_distribution_ptr priorDistribution = class_distribution(train_set);
    Hash_map_ptr w = create_string_hash_map();
    Hash_map_ptr w0 = create_string_hash_map();
    Hash_map_ptr W = create_string_hash_map();
    for (int i = 0; i < size_of_partition(class_lists); i++){
        Instance_list_ptr class_list = get_instance_list(class_lists, i);
        char* C_i = get_instance(class_list, 0)->class_label;
        Vector_ptr average_vector = create_vector(continuous_attribute_average2(class_list));
        Matrix_ptr class_covariance = covariance(class_list, average_vector);
        double det = determinant(class_covariance);
        inverse(class_covariance);
        Matrix_ptr Wi = clone(class_covariance);
        multiply_with_constant(Wi, -0.5);
        hash_map_insert(W, C_i, Wi);
        Vector_ptr wi = multiply_with_vector_from_left(class_covariance, average_vector);
        free_matrix(class_covariance);
        hash_map_insert(w, C_i, wi);
        double* w0i = malloc(sizeof(double));
        *w0i = -0.5 * (dot_product(wi, average_vector) + log(det)) + log(get_probability(priorDistribution, C_i));
        hash_map_insert(w0, C_i, w0i);
        free_vector(average_vector);
    }
    free_partition(class_lists);
    result->model = create_qda_model(priorDistribution, W, w, w0);
    result->predict = predict_qda;
    result->predict_probability = NULL;
    return result;
}

Classifier_ptr load_qda(const char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_qda_model2(file_name);
    result->predict = predict_qda;
    result->predict_probability = NULL;
    return result;
}

void free_qda(Classifier_ptr qda) {
    free_qda_model(qda->model);
    free(qda);
}
