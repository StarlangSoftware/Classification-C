//
// Created by Olcay Taner YILDIZ on 28.06.2023.
//

#include <FileUtils.h>
#include <Vector.h>
#include <Matrix.h>
#include <float.h>
#include <Memory/Memory.h>
#include <math.h>
#include "QdaModel.h"
#include "../../InstanceList/Partition.h"

/**
 * The constructor which sets the priorDistribution, w w1 and HashMap of String Matrix.
 *
 * @param prior_distribution DiscreteDistribution input.
 * @param W                 HashMap of String and Matrix.
 * @param w                 HashMap of String and Vectors.
 * @param w0                HashMap of String and Double.
 */
Qda_model_ptr
create_qda_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr W, Hash_map_ptr w, Hash_map_ptr w0) {
    Qda_model_ptr result = malloc_(sizeof(Qda_model), "create_qda_model");
    result->prior_distribution = prior_distribution;
    result->W = W;
    result->w = w;
    result->w0 = w0;
    return result;
}

/**
 * Loads a quadratic discriminant analysis model from an input model file.
 * @param file_name Model file name.
 */
Qda_model_ptr create_qda_model2(const char *file_name) {
    Qda_model_ptr result = malloc_(sizeof(Qda_model), "create_qda_model2");
    FILE* input_file = fopen(file_name, "r");
    result->w = create_string_hash_map();
    result->w0 = create_string_hash_map();
    result->prior_distribution = create_discrete_distribution2(input_file);
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        char class_label[MAX_LINE_LENGTH];
        double* weight = malloc_(sizeof(double), "create_qda_model2");
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

/**
 * Frees memory allocated for Qda model
 * @param qda_model Qda model
 */
void free_qda_model(Qda_model_ptr qda_model) {
    free_discrete_distribution(qda_model->prior_distribution);
    free_hash_map(qda_model->W, (void (*)(void *)) free_matrix);
    free_hash_map(qda_model->w, (void (*)(void *)) free_vector);
    free_hash_map(qda_model->w0, free_);
    free_(qda_model);
}

/**
 * The calculateMetric method takes an Instance and a String as inputs. It multiplies Matrix Wi with Vector xi
 * then calculates the dot product of it with xi. Then, again it finds the dot product of wi and xi and returns the summation with w0i.
 *
 * @param qda_model Current qda model
 * @param instance Instance input.
 * @param C_i       String input.
 * @return The result of Wi.multiplyWithVectorFromLeft(xi).dotProduct(xi) + wi.dotProduct(xi) + w0i.
 */
double calculate_metric_qda(const Qda_model *qda_model, const Instance *instance, const char *C_i) {
    double w0i;
    Vector_ptr xi = to_vector(instance);
    Matrix_ptr Wi = hash_map_get(qda_model->W, C_i);
    Vector_ptr wi = hash_map_get(qda_model->w, C_i);
    w0i = *(double*)hash_map_get(qda_model->w0, C_i);
    Vector_ptr tmp = multiply_with_vector_from_left(Wi, xi);
    double result = dot_product(tmp, xi) + dot_product(wi, xi) + w0i;
    free_vector(xi);
    free_vector(tmp);
    return result;
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
    free_array_list(possible_labels, NULL);
    return predicted_class;
}

/**
 * Training algorithm for the quadratic discriminant analysis classifier (Introduction to Machine Learning, Alpaydin, 2015).
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter -
 */
Model_ptr train_qda(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_qda_1");
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
        double* w0i = malloc_(sizeof(double), "train_qda_2");
        *w0i = -0.5 * (dot_product(wi, average_vector) + log(det)) + log(get_probability(priorDistribution, C_i));
        hash_map_insert(w0, C_i, w0i);
        free_vector(average_vector);
    }
    free_partition(class_lists);
    result->model = create_qda_model(priorDistribution, W, w, w0);
    result->train = train_qda;
    result->predict = predict_qda;
    result->predict_probability = NULL;
    return result;
}

/**
 * Loads the Qda model from an input file.
 * @param file_name File name of the Qda model.
 */
Model_ptr load_qda(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_qda");
    result->model = create_qda_model2(file_name);
    result->train = train_qda;
    result->predict = predict_qda;
    result->predict_probability = NULL;
    return result;
}

/**
 * Frees memory allocated for Qda model.
 * @param qda Qda model.
 */
void free_qda(Model_ptr qda) {
    free_qda_model(qda->model);
    free_(qda);
}
