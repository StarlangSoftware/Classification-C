//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#include <FileUtils.h>
#include <Vector.h>
#include <math.h>
#include <float.h>
#include <Memory/Memory.h>
#include "NaiveBayesModel.h"
#include "../../InstanceList/Partition.h"

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

/**
 * Training algorithm for Naive Bayes algorithm. It basically calls trainContinuousVersion for continuous data sets,
 * trainDiscreteVersion for discrete data sets.
 * @param trainSet Training data given to the algorithm
 * @param parameters -
 */
Model_ptr train_naive_bayes(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_naive_bayes");
    Discrete_distribution_ptr prior_distribution = class_distribution(train_set);
    Partition_ptr class_lists = create_partition3(train_set);
    train_continuous_version(result, prior_distribution, class_lists);
    free_partition(class_lists);
    result->predict_probability = NULL;
    result->predict = predict_naive_bayes;
    result->train = train_naive_bayes;
    return result;
}

/**
 * Training algorithm for Naive Bayes algorithm with a continuous data set.
 *
 * @param priorDistribution Probability distribution of classes P(C_i)
 * @param classLists        Instances are divided into K lists, where each list contains only instances from a single class
 */
void train_continuous_version(Model_ptr classifier, Discrete_distribution_ptr prior_distribution,
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
Model_ptr load_naive_bayes(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_naive_bayes");
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
void free_naive_bayes(Model_ptr naive_bayes) {
    free_naive_bayes_model(naive_bayes->model);
    free_(naive_bayes);
}
