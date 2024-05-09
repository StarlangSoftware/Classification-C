//
// Created by Olcay Taner YILDIZ on 21.06.2023.
//

#include <Memory/Memory.h>
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
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_random");
    Discrete_distribution_ptr distribution = class_distribution(train_set);
    Array_list_ptr items = get_items(distribution);
    free_discrete_distribution(distribution);
    result->model = create_random_model(items);
    result->train = train_random;
    result->predict = predict_random;
    result->predict_probability = predict_probability_random;
    return result;
}

/**
 * Loads the random classifier model from an input file.
 * @param file_name File name of the random classifier model.
 */
Classifier_ptr load_random(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_random");
    result->model = create_random_model2(file_name);
    result->train = train_random;
    result->predict = predict_random;
    result->predict_probability = predict_probability_random;
    return result;
}

/**
 * Frees memory allocated for random classifier model
 * @param random Random model
 */
void free_random(Classifier_ptr random) {
    free_random_model(random->model);
    free_(random);
}
