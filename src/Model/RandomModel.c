//
// Created by Olcay Taner YILDIZ on 21.06.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "RandomModel.h"
#include <FileUtils.h>
#include <Memory/Memory.h>

/**
 * A constructor that sets the class labels.
 *
 * @param classLabels An ArrayList of class labels.
 */
Random_model_ptr create_random_model(Array_list_ptr class_labels) {
    Random_model_ptr result = malloc_(sizeof(Random_model), "create_random_model");
    result->class_labels = class_labels;
    return result;
}

/**
 * Loads a random classifier model from an input model file.
 * @param file_name Model file name.
 */
Random_model_ptr create_random_model2(const char *file_name) {
    Random_model_ptr result = malloc_(sizeof(Random_model), "create_random_model2");
    result->class_labels = create_array_list();
    FILE* input_file = fopen(file_name, "r");
    fscanf(input_file, "%d", &(result->seed));
    int size;
    fscanf(input_file, "%d", &size);
    for (int i = 0; i < size; i++){
        char class_label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", class_label);
        array_list_add(result->class_labels, class_label);
    }
    fclose(input_file);
    return result;
}

/**
 * The predict method gets an Instance as an input and retrieves the possible class labels as an ArrayList. Then selects a
 * random number as an index and returns the class label at this selected index.
 *
 * @param instance Instance to make prediction.
 * @return The class label at the randomly selected index.
 */
char *predict_random(const void* model, const Instance* instance) {
    Random_model_ptr random_model = (Random_model_ptr) model;
    int size = random_model->class_labels->size;
    int index = random() % size;
    return array_list_get(random_model->class_labels, index);
}

/**
 * Calculates the posterior probability distribution for the given instance according to random model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr predict_probability_random(const void* model, const Instance* instance) {
    Random_model_ptr random_model = (Random_model_ptr) model;
    Hash_map_ptr result = create_string_hash_map();
    for (int i = 0; i < random_model->class_labels->size; i++){
        char* class_label = array_list_get(random_model->class_labels, i);
        double* p = malloc_(sizeof(double), "predict_probability_random");
        *p = 1.0 / random_model->class_labels->size;
        hash_map_insert(result, class_label, p);
    }
    return result;
}

/**
 * Frees memory allocated for random model
 * @param random_model Random model
 */
void free_random_model(Random_model_ptr random_model) {
    free_array_list(random_model->class_labels, NULL);
    free_(random_model);
}

/**
 * Training algorithm for random classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
Model_ptr train_random(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_random");
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
Model_ptr load_random(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_random");
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
void free_random(Model_ptr random) {
    free_random_model(random->model);
    free_(random);
}
