//
// Created by Olcay Taner YILDIZ on 21.07.2023.
//

#include <stdlib.h>
#include "DeepNetwork.h"
#include "../InstanceList/Partition.h"

/**
 * Training algorithm for deep network classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the deep network algorithm. crossValidationRatio and seed are used as parameters.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
Classifier_ptr train_deep_network(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    Deep_network_parameter_ptr deep_network_parameter = (Deep_network_parameter_ptr) parameter;
    Partition_ptr partition = create_partition4(train_set, deep_network_parameter->cross_validation_ratio, deep_network_parameter->seed, true);
    result->model = create_deep_network_model(get_instance_list(partition, 1), get_instance_list(partition, 0), deep_network_parameter);
    result->train = train_deep_network;
    result->predict_probability = predict_probability_deep_network;
    result->predict = predict_deep_network;
    return result;
}

Classifier_ptr load_deep_network(const char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_deep_network_model2(file_name);
    result->train = train_deep_network;
    result->predict_probability = predict_probability_deep_network;
    result->predict = predict_deep_network;
    return result;
}

Classifier_ptr validation_deep_network(Deep_network_model_ptr deep_network) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = deep_network;
    result->train = train_deep_network;
    result->predict_probability = predict_probability_deep_network;
    result->predict = predict_deep_network;
    return result;
}

void free_deep_network(Classifier_ptr deep_network) {
    free_deep_network_model(deep_network->model);
    free(deep_network);
}
