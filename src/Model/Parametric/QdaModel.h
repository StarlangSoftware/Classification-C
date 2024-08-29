//
// Created by Olcay Taner YILDIZ on 28.06.2023.
//

#ifndef CLASSIFICATION_QDAMODEL_H
#define CLASSIFICATION_QDAMODEL_H

#include <DiscreteDistribution.h>
#include "../../Instance/Instance.h"
#include "../../InstanceList/InstanceList.h"
#include "../Model.h"

struct qda_model{
    Discrete_distribution_ptr prior_distribution;
    Hash_map_ptr w0;
    Hash_map_ptr w;
    Hash_map_ptr W;
};

typedef struct qda_model Qda_model;

typedef Qda_model *Qda_model_ptr;

Qda_model_ptr create_qda_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr W, Hash_map_ptr w, Hash_map_ptr w0);

Qda_model_ptr create_qda_model2(const char* file_name);

void free_qda_model(Qda_model_ptr qda_model);

double calculate_metric_qda(const Qda_model* qda_model, const Instance* instance, const char* C_i);

char* predict_qda(const void* model, const Instance* instance);

Model_ptr train_qda(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_qda(const char* file_name);

void free_qda(Model_ptr qda);

#endif //CLASSIFICATION_QDAMODEL_H
