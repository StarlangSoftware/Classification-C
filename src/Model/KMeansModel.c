//
// Created by Olcay Taner YILDIZ on 22.06.2023.
//

#include <float.h>
#include <string.h>
#include "KMeansModel.h"
#include "../DistanceMetric/EuclidianDistance.h"
#include "Memory/Memory.h"

/**
 * The constructor that sets the classMeans, priorDistribution and distanceMetric according to given inputs.
 *
 * @param priorDistribution DiscreteDistribution input.
 * @param classMeans        InstanceList of class means.
 * @param distanceMetric    DistanceMetric input.
 */
K_means_model_ptr create_k_means_model(Discrete_distribution_ptr prior_distribution, Instance_list_ptr class_means,
                                       double (*distance_metric)(const Instance *, const Instance *, const void *)) {
    K_means_model_ptr result = malloc_(sizeof(K_means_model), "create_k_means_model");
    result->prior_distribution = prior_distribution;
    result->class_means = class_means;
    result->distance_metric = distance_metric;
    return result;
}

/**
 * Frees memory allocated for k-means model
 * @param k_means_model K-means model
 */
void free_k_means_model(K_means_model_ptr k_means_model) {
    free_discrete_distribution(k_means_model->prior_distribution);
    free_instance_list(k_means_model->class_means);
    free_(k_means_model);
}

/**
 * Loads a K-means model from an input model file.
 * @param file_name Model file name.
 */
K_means_model_ptr create_k_means_model2(const char *file_name) {
    K_means_model_ptr result = malloc_(sizeof(K_means_model), "create_k_means_model2");
    FILE* input_file = fopen(file_name, "r");
    result->prior_distribution = create_discrete_distribution2(input_file);
    result->distance_metric = euclidian_distance;
    result->class_means = create_instance_list4(input_file);
    fclose(input_file);
    return result;
}

char *predict_k_means(const void *model, const Instance* instance) {
    K_means_model_ptr k_means_model = (K_means_model_ptr) model;
    double max_metric = -DBL_MAX;
    char* predicted_class = get_max_item(k_means_model->prior_distribution);
    int size = size_of_distribution(k_means_model->prior_distribution);
    Array_list_ptr possible_labels = get_items(k_means_model->prior_distribution);
    for (int i = 0; i < size; i++){
        char* C_i = array_list_get(possible_labels, i);
        if (contains_distribution(k_means_model->prior_distribution, C_i)){
            double metric = calculate_metric_k_means(model, instance, C_i);
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
 * The calculateMetric method takes an Instance and a String as inputs. It loops through the class means, if
 * the corresponding class label is same as the given String it returns the negated distance between given instance and the
 * current item of class means. Otherwise it returns the smallest negative number.
 *
 * @param instance Instance input.
 * @param Ci       String input.
 * @return The negated distance between given instance and the current item of class means.
 */
double calculate_metric_k_means(const K_means_model* k_means_model, const Instance *instance, const char *C_i) {
    for (int i = 0; i < size_of_instance_list(k_means_model->class_means); i++) {
        Instance_ptr class_mean = get_instance(k_means_model->class_means, i);
        if (strcmp(class_mean->class_label, C_i) == 0) {
            return -k_means_model->distance_metric(instance, class_mean, NULL);
        }
    }
    return -DBL_MAX;
}
