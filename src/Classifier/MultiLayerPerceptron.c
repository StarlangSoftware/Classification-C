//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#include <stdlib.h>
#include "MultiLayerPerceptron.h"
#include "../InstanceList/Partition.h"

/**
 * Training algorithm for the multilayer perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the multilayer perceptron with
 * gradient descent.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the multilayer perceptron.
 */
Classifier_ptr train_multi_layer_perceptron(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    Multi_layer_perceptron_parameter_ptr multi_layer_perceptron_parameter = (Multi_layer_perceptron_parameter_ptr) parameter;
    Partition_ptr partition = create_partition4(train_set, multi_layer_perceptron_parameter->cross_validation_ratio, multi_layer_perceptron_parameter->seed, true);
    result->model = create_multi_layer_perceptron_model(get_instance_list(partition, 1), get_instance_list(partition, 0), multi_layer_perceptron_parameter);
    result->predict_probability = predict_probability_multi_layer_perceptron;
    result->predict = predict_multi_layer_perceptron;
    return result;
}

Classifier_ptr load_multi_layer_perceptron(const char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_multi_layer_perceptron_model2(file_name);
    result->predict_probability = predict_probability_multi_layer_perceptron;
    result->predict = predict_multi_layer_perceptron;
    return result;

}

Classifier_ptr validation_multi_layer_perceptron(Multi_layer_perceptron_model_ptr multi_layer_perceptron) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = multi_layer_perceptron;
    result->predict_probability = predict_probability_multi_layer_perceptron;
    result->predict = predict_multi_layer_perceptron;
    return result;
}

void free_multi_layer_perceptron(Classifier_ptr multi_layer_perceptron) {
    free_multi_layer_perceptron_model(multi_layer_perceptron->model);
    free(multi_layer_perceptron);
}
