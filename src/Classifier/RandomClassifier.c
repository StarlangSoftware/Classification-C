//
// Created by Olcay Taner YILDIZ on 21.06.2023.
//

#include <stdlib.h>
#include "RandomClassifier.h"
#include "../Model/RandomModel.h"
#include "../Model/DummyModel.h"

/**
 * Training algorithm for random classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
Classifier_ptr train_random(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_random_model(get_items(class_distribution(train_set)));
    result->train = train_random;
    result->predict = predict_random;
    result->predict_probability = predict_probability_random;
    return result;
}

Classifier_ptr load_random(const char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_random_model2(file_name);
    result->train = train_random;
    result->predict = predict_random;
    result->predict_probability = predict_probability_random;
    return result;
}

void free_random(Classifier_ptr random) {
    free_random_model(random->model);
    free(random);
}
