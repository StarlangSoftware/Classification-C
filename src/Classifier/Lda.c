//
// Created by Olcay Taner YILDIZ on 26.06.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "Lda.h"
#include "../Model/LdaModel.h"
#include "../InstanceList/Partition.h"

/**
 * Training algorithm for the linear discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
Classifier_ptr train_lda(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_lda_1");
    result->train = train_lda;
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
    result->predict = predict_lda;
    result->predict_probability = NULL;
    return result;
}

/**
 * Loads the Lda model from an input file.
 * @param file_name File name of the Lda model.
 */
Classifier_ptr load_lda(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_lda");
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
void free_lda(Classifier_ptr lda) {
    free_lda_model(lda->model);
    free_(lda);
}
