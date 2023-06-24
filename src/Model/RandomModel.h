//
// Created by Olcay Taner YILDIZ on 21.06.2023.
//

#ifndef CLASSIFICATION_RANDOMMODEL_H
#define CLASSIFICATION_RANDOMMODEL_H

#include <ArrayList.h>
#include <HashMap/HashMap.h>
#include "../Instance/Instance.h"

struct random_model{
    int seed;
    Array_list_ptr class_labels;
};

typedef struct random_model Random_model;

typedef Random_model *Random_model_ptr;

Random_model_ptr create_random_model(Array_list_ptr class_labels);

Random_model_ptr create_random_model2(const char* file_name);

char* predict_random(const void* model, const Instance* instance);

Hash_map_ptr predict_probability_random(const void* model, const Instance* instance);

void free_random_model(Random_model_ptr random_model);

#endif //CLASSIFICATION_RANDOMMODEL_H
