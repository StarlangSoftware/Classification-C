//
// Created by Olcay Taner YILDIZ on 28.06.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include <Vector.h>
#include <Matrix.h>
#include <float.h>
#include "QdaModel.h"

/**
 * The constructor which sets the priorDistribution, w w1 and HashMap of String Matrix.
 *
 * @param priorDistribution {@link DiscreteDistribution} input.
 * @param W                 {@link HashMap} of String and Matrix.
 * @param w                 {@link HashMap} of String and Vectors.
 * @param w0                {@link HashMap} of String and Double.
 */
Qda_model_ptr
create_qda_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr W, Hash_map_ptr w, Hash_map_ptr w0) {
    Qda_model_ptr result = malloc(sizeof(Qda_model));
    result->prior_distribution = prior_distribution;
    result->W = W;
    result->w = w;
    result->w0 = w0;
    return result;
}

Qda_model_ptr create_qda_model2(const char *file_name) {
    Qda_model_ptr result = malloc(sizeof(Qda_model));
    FILE* input_file = fopen(file_name, "r");
    result->w = create_string_hash_map();
    result->w0 = create_string_hash_map();
    result->prior_distribution = create_discrete_distribution2(input_file);
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        char class_label[MAX_LINE_LENGTH];
        double* weight = malloc(sizeof(double));
        fscanf(input_file, "%s %lf", class_label, weight);
        hash_map_insert(result->w0, class_label, weight);
    }
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        char class_label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", class_label);
        Vector_ptr vector = create_vector5(input_file);
        hash_map_insert(result->w, class_label, vector);
    }
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        char class_label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", class_label);
        Matrix_ptr matrix = create_matrix5(input_file);
        hash_map_insert(result->W, class_label, matrix);
    }
    fclose(input_file);
    return result;
}

void free_qda_model(Qda_model_ptr qda_model) {
    free_discrete_distribution(qda_model->prior_distribution);
    free_hash_map(qda_model->W, free);
    free_hash_map(qda_model->w, free);
    free_hash_map(qda_model->w0, free);
    free(qda_model);
}

/**
 * The calculateMetric method takes an {@link Instance} and a String as inputs. It multiplies Matrix Wi with Vector xi
 * then calculates the dot product of it with xi. Then, again it finds the dot product of wi and xi and returns the summation with w0i.
 *
 * @param instance {@link Instance} input.
 * @param Ci       String input.
 * @return The result of Wi.multiplyWithVectorFromLeft(xi).dotProduct(xi) + wi.dotProduct(xi) + w0i.
 */
double calculate_metric_qda(const Qda_model *qda_model, const Instance *instance, const char *C_i) {
    double w0i;
    Vector_ptr xi = to_vector(instance);
    Matrix_ptr Wi = hash_map_get(qda_model->W, C_i);
    Vector_ptr wi = hash_map_get(qda_model->w, C_i);
    w0i = *(double*)hash_map_get(qda_model->w0, C_i);
    return dot_product(multiply_with_vector_from_left(Wi, xi), xi) + dot_product(wi, xi) + w0i;
}

char *predict_qda(const void *model, const Instance *instance) {
    Qda_model_ptr qda_model = (Qda_model_ptr) model;
    double max_metric = -DBL_MAX;
    char* predicted_class = get_max_item(qda_model->prior_distribution);
    int size = size_of_distribution(qda_model->prior_distribution);
    Array_list_ptr possible_labels = get_items(qda_model->prior_distribution);
    for (int i = 0; i < size; i++){
        char* C_i = array_list_get(possible_labels, i);
        if (contains_distribution(qda_model->prior_distribution, C_i)){
            double metric = calculate_metric_qda(model, instance, C_i);
            if (metric > max_metric){
                max_metric = metric;
                predicted_class = C_i;
            }
        }
    }
    return predicted_class;
}
