//
// Created by Olcay Taner YILDIZ on 25.06.2023.
//

#include <Memory/Memory.h>
#include "Knn.h"
#include "../Model/KnnModel.h"
#include "../Parameter/KnnParameter.h"

void free_knn(Classifier_ptr knn) {
    free_knn_model(knn->model);
    free_(knn);
}

/**
 * Training algorithm for K-nearest neighbor classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters K: k parameter of the K-nearest neighbor algorithm
 *                   distanceMetric: distance metric used to calculate the distance between two instances.
 */
Classifier_ptr train_knn(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_knn");
    result->model = create_knn_model(train_set, ((Knn_parameter_ptr)(parameter))->k, ((Knn_parameter_ptr)(parameter))->distance_function);
    result->train = train_knn;
    result->predict = predict_knn;
    result->predict_probability = predict_probability_knn;
    return result;
}

Classifier_ptr load_knn(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_knn");
    result->model = create_knn_model2(file_name);
    result->train = train_knn;
    result->predict = predict_knn;
    result->predict_probability = predict_probability_knn;
    return result;
}
