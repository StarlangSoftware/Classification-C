//
// Created by Olcay Taner YILDIZ on 23.06.2023.
//

#include <Memory/Memory.h>
#include "KMeans.h"
#include "../Model/KMeansModel.h"
#include "../InstanceList/Partition.h"
#include "../Parameter/KMeansParameter.h"

/**
 * Training algorithm for KMeans classifier. KMeans finds the mean of each class for training.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters distanceMetric: distance metric used to calculate the distance between two instances.
 */
Classifier_ptr train_k_means(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_k_means");
    Discrete_distribution_ptr prior_distribution = class_distribution(train_set);
    Instance_list_ptr class_means = create_instance_list();
    Partition_ptr class_lists = create_partition3(train_set);
    for (int i = 0; i < size_of_partition(class_lists); i++) {
        add_instance(class_means, average(get_instance_list(class_lists, i)));
    }
    free_partition(class_lists);
    result->model = create_k_means_model(prior_distribution, class_means, ((K_means_parameter_ptr)(parameter))->distance_function);
    result->train = train_k_means;
    result->predict = predict_k_means;
    result->predict_probability = NULL;
    return result;
}

/**
 * Loads the K-means model from an input file.
 * @param file_name File name of the K-means model.
 */
Classifier_ptr load_k_means(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_k_means");
    result->model = create_k_means_model2(file_name);
    result->train = train_k_means;
    result->predict = predict_k_means;
    result->predict_probability = NULL;
    return result;
}

/**
 * Frees memory allocate for K-means model.
 * @param k_means K-means model
 */
void free_k_means(Classifier_ptr k_means) {
    free_k_means_model(k_means->model);
    free_(k_means);
}
