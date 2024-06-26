//
// Created by Olcay Taner YILDIZ on 18.07.2023.
//

#include <Memory/Memory.h>
#include "LinearPerceptron.h"
#include "../InstanceList/Partition.h"

Classifier_ptr validation_linear_perceptron(Linear_perceptron_model_ptr linear_perceptron) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "validation_linear_perceptron");
    result->model = linear_perceptron;
    result->train = train_linear_perceptron;
    result->predict_probability = predict_probability_linear_perceptron;
    result->predict = predict_linear_perceptron;
    return result;
}

/**
 * Training algorithm for the linear perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the linear perceptron with
 * gradient descent.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the linear perceptron.
 */
Classifier_ptr train_linear_perceptron(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_linear_perceptron");
    Linear_perceptron_parameter_ptr linear_perceptron_parameter = (Linear_perceptron_parameter_ptr) parameter;
    Partition_ptr partition = create_partition4(train_set, linear_perceptron_parameter->cross_validation_ratio, linear_perceptron_parameter->seed, true);
    result->model = create_linear_perceptron_model(get_instance_list(partition, 1), get_instance_list(partition, 0), linear_perceptron_parameter);
    result->train = train_linear_perceptron;
    result->predict_probability = predict_probability_linear_perceptron;
    result->predict = predict_linear_perceptron;
    free_partition(partition);
    return result;
}

/**
 * Loads the linear perceptron model from an input file.
 * @param file_name File name of the linear perceptron model.
 */
Classifier_ptr load_linear_perceptron(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_linear_perceptron");
    result->model = create_linear_perceptron_model2(file_name);
    result->train = train_linear_perceptron;
    result->predict_probability = predict_probability_linear_perceptron;
    result->predict = predict_linear_perceptron;
    return result;
}

/**
 * Frees memory allocated for linear perceptron model
 * @param linear_perceptron Linear perceptron model
 */
void free_linear_perceptron(Classifier_ptr linear_perceptron) {
    free_linear_perceptron_model(linear_perceptron->model);
    free_(linear_perceptron);
}
