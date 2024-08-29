//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#ifndef CLASSIFICATION_DUMMYMODEL_H
#define CLASSIFICATION_DUMMYMODEL_H

#include <DiscreteDistribution.h>
#include "../InstanceList/InstanceList.h"
#include "Model.h"

struct dummy_model{
    Discrete_distribution_ptr distribution;
};

typedef struct dummy_model Dummy_model;

typedef Dummy_model *Dummy_model_ptr;

Dummy_model_ptr create_dummy_model(Instance_list_ptr train_set);

Dummy_model_ptr create_dummy_model2(const char* file_name);

void free_dummy_model(Dummy_model_ptr dummy_model);

char* predict_dummy(const void* model, const Instance* instance);

Hash_map_ptr predict_probability_dummy(const void* model, const Instance* instance);

Model_ptr train_dummy(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_dummy(const char* file_name);

void free_dummy(Model_ptr dummy);

#endif //CLASSIFICATION_DUMMYMODEL_H
