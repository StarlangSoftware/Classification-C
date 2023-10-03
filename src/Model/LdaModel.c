//
// Created by Olcay Taner YILDIZ on 26.06.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include <Vector.h>
#include <float.h>
#include "LdaModel.h"

/**
 * A constructor which sets the priorDistribution, w and w1 according to given inputs.
 *
 * @param priorDistribution DiscreteDistribution input.
 * @param w                 HashMap of String and Vectors.
 * @param w0                HashMap of String and Double.
 */
Lda_model_ptr create_lda_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr w, Hash_map_ptr w0) {
    Lda_model_ptr result = malloc(sizeof(Lda_model));
    result->prior_distribution = prior_distribution;
    result->w = w;
    result->w0 = w0;
    return result;
}

Lda_model_ptr create_lda_model2(const char *file_name) {
    Lda_model_ptr result = malloc(sizeof(Lda_model));
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
    fclose(input_file);
    return result;
}

/**
 * The calculateMetric method takes an Instance and a String as inputs. It returns the dot product of given Instance
 * and w0 plus w1.
 *
 * @param instance Instance input.
 * @param Ci       String input.
 * @return The dot product of given Instance and w0 plus w1.
 */
double calculate_metric_lda(const Lda_model *lda_model, const Instance *instance, const char *C_i) {
    double w0i;
    Vector_ptr xi = to_vector(instance);
    Vector_ptr wi = hash_map_get(lda_model->w, C_i);
    w0i = *(double*)hash_map_get(lda_model->w0, C_i);
    return dot_product(wi, xi) + w0i;
}

void free_lda_model(Lda_model_ptr lda_model) {
    free_discrete_distribution(lda_model->prior_distribution);
    free_hash_map(lda_model->w, free);
    free_hash_map(lda_model->w0, free);
    free(lda_model);
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
    return predicted_class;
}
