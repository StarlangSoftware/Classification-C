//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#include <FileUtils.h>
#include <Vector.h>
#include <math.h>
#include <float.h>
#include <Memory/Memory.h>
#include "NaiveBayesModel.h"

/**
 * A constructor that sets the priorDistribution, classMeans and classDeviations.
 *
 * @param priorDistribution DiscreteDistribution input.
 * @param classMeans        A HashMap of String and Vector.
 * @param classDeviations   A HashMap of String and Vector.
 */
Naive_bayes_model_ptr create_naive_bayes_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr class_means,
                                               Hash_map_ptr class_deviations) {
    Naive_bayes_model_ptr result = malloc_(sizeof(Naive_bayes_model), "create_naive_bayes_model");
    result->prior_distribution = prior_distribution;
    result->class_means = class_means;
    result->class_deviations = class_deviations;
    return result;
}

/**
 * Loads a naive Bayes model from an input model file.
 * @param file_name Model file name.
 */
Naive_bayes_model_ptr create_naive_bayes_model2(const char *file_name) {
    char class_label[MAX_LINE_LENGTH];
    Naive_bayes_model_ptr result = malloc_(sizeof(Naive_bayes_model), "create_naive_bayes_model2");
    FILE* input_file = fopen(file_name, "r");
    result->prior_distribution = create_discrete_distribution2(input_file);
    result->class_means = create_string_hash_map();
    result->class_deviations = create_string_hash_map();
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        fscanf(input_file, "%s", class_label);
        Vector_ptr vector = create_vector5(input_file);
        hash_map_insert(result->class_means, class_label, vector);
    }
    for (int i = 0; i < size_of_distribution(result->prior_distribution); i++){
        fscanf(input_file, "%s", class_label);
        Vector_ptr vector = create_vector5(input_file);
        hash_map_insert(result->class_deviations, class_label, vector);
    }
    fclose(input_file);
    return result;
}

/**
 * The logLikelihoodContinuous method takes an Instance and a class label as inputs. First it gets the logarithm
 * of given class label's probability via prior distribution as logLikelihood. Then it loops times of given instance attribute size, and accumulates the
 * logLikelihood by calculating -0.5 * ((xi - mi) / si )** 2).
 *
 * @param classLabel String input class label.
 * @param instance   Instance input.
 * @return The log likelihood of given class label and Instance.
 */
double log_likelihood_continuous(const Naive_bayes_model* model, const char *class_label, const Instance *instance) {
    double xi, mi, si;
    double logLikelihood = log(get_probability(model->prior_distribution, class_label));
    for (int i = 0; i < attribute_size(instance); i++) {
        xi = get_attribute(instance, i)->float_value;
        Vector_ptr m = hash_map_get(model->class_means, class_label);
        mi = get_value(m, i);
        Vector_ptr s = hash_map_get(model->class_deviations, class_label);
        si = get_value(s, i);
        logLikelihood += -0.5 * pow((xi - mi) / si, 2);
    }
    return logLikelihood;
}

char *predict_naive_bayes(const void *model, const Instance *instance) {
    Naive_bayes_model_ptr k_means_model = (Naive_bayes_model_ptr) model;
    double max_metric = -DBL_MAX;
    char* predicted_class = get_max_item(k_means_model->prior_distribution);
    int size = size_of_distribution(k_means_model->prior_distribution);
    Array_list_ptr possible_labels = get_items(k_means_model->prior_distribution);
    for (int i = 0; i < size; i++){
        char* C_i = array_list_get(possible_labels, i);
        if (contains_distribution(k_means_model->prior_distribution, C_i)){
            double metric = log_likelihood_continuous(model, C_i, instance);
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
 * Frees memory allocated for naive Bayes model.
 * @param model Naive Bayes model.
 */
void free_naive_bayes_model(Naive_bayes_model_ptr model) {
    free_discrete_distribution(model->prior_distribution);
    free_hash_map(model->class_means, (void (*)(void *)) free_vector);
    free_hash_map(model->class_deviations, (void (*)(void *)) free_vector);
    free_(model);
}
