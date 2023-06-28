//
// Created by Olcay Taner YILDIZ on 21.06.2023.
//

#include <stdlib.h>
#include <stdio.h>
#include "RandomModel.h"
#include <FileUtils.h>

/**
 * A constructor that sets the class labels.
 *
 * @param classLabels An ArrayList of class labels.
 */
Random_model_ptr create_random_model(Array_list_ptr class_labels) {
    Random_model_ptr result = malloc(sizeof(Random_model));
    result->class_labels = class_labels;
    return result;
}

Random_model_ptr create_random_model2(const char *file_name) {
    Random_model_ptr result = malloc(sizeof(Random_model));
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
 * @param instance {@link Instance} to make prediction.
 * @return The class label at the randomly selected index.
 */
char *predict_random(const void* model, const Instance* instance) {
    Random_model_ptr random_model = (Random_model_ptr) model;
    int size = random_model->class_labels->size;
    int index = random() % size;
    return array_list_get(random_model->class_labels, index);
}

Hash_map_ptr predict_probability_random(const void* model, const Instance* instance) {
    Random_model_ptr random_model = (Random_model_ptr) model;
    Hash_map_ptr result = create_string_hash_map();
    for (int i = 0; i < random_model->class_labels->size; i++){
        char* class_label = array_list_get(random_model->class_labels, i);
        double* p = malloc(sizeof(double));
        *p = 1.0 / random_model->class_labels->size;
        hash_map_insert(result, class_label, p);
    }
    return result;
}

void free_random_model(Random_model_ptr random_model) {
    free_array_list(random_model->class_labels, free);
    free(random_model);
}
