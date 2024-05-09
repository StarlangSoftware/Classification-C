//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#include <Memory/Memory.h>
#include "NaiveBayes.h"
#include "../Model/NaiveBayesModel.h"

/**
 * Training algorithm for Naive Bayes algorithm. It basically calls trainContinuousVersion for continuous data sets,
 * trainDiscreteVersion for discrete data sets.
 * @param trainSet Training data given to the algorithm
 * @param parameters -
 */
Classifier_ptr train_naive_bayes(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_naive_bayes");
    Discrete_distribution_ptr prior_distribution = class_distribution(train_set);
    Partition_ptr class_lists = create_partition3(train_set);
    train_continuous_version(result, prior_distribution, class_lists);
    free_partition(class_lists);
    result->train = train_naive_bayes;
    result->predict_probability = NULL;
    result->predict = predict_naive_bayes;
    return result;
}

/**
 * Training algorithm for Naive Bayes algorithm with a continuous data set.
 *
 * @param priorDistribution Probability distribution of classes P(C_i)
 * @param classLists        Instances are divided into K lists, where each list contains only instances from a single class
 */
void train_continuous_version(Classifier_ptr classifier, Discrete_distribution_ptr prior_distribution,
                              Partition_ptr class_lists) {
    Hash_map_ptr class_means = create_string_hash_map();
    Hash_map_ptr class_deviations = create_string_hash_map();
    for (int i = 0; i < size_of_partition(class_lists); i++) {
        Instance_list_ptr class_list = get_instance_list(class_lists, i);
        char *class_label = get_instance(class_list, 0)->class_label;
        Vector_ptr average_vector = create_vector(continuous_attribute_average2(class_list));
        hash_map_insert(class_means, class_label, average_vector);
        Vector_ptr standard_deviation_vector = create_vector(continuous_attribute_standard_deviation2(class_list));
        hash_map_insert(class_deviations, class_label, standard_deviation_vector);
    }
    classifier->model = create_naive_bayes_model(prior_distribution, class_means, class_deviations);
}

/**
 * Loads the naive Bayes model from an input file.
 * @param fileName File name of the naive Bayes model.
 */
Classifier_ptr load_naive_bayes(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_naive_bayes");
    result->model = create_naive_bayes_model2(file_name);
    result->train = train_naive_bayes;
    result->predict = predict_naive_bayes;
    result->predict_probability = NULL;
    return result;
}

/**
 * Frees memory allocated for naive Bayes model
 * @param naive_bayes Naive Bayes model
 */
void free_naive_bayes(Classifier_ptr naive_bayes) {
    free_naive_bayes_model(naive_bayes->model);
    free_(naive_bayes);
}
