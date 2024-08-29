//
// Created by Olcay Taner YILDIZ on 29.08.2024.
//

#ifndef CLASSIFICATION_MODEL_H
#define CLASSIFICATION_MODEL_H

#include <HashMap/HashMap.h>
#include "../Instance/Instance.h"
#include "../Performance/DetailedClassificationPerformance.h"
#include "../InstanceList/InstanceList.h"

struct model{
    void* model;
    struct model* (*train)(Instance_list_ptr train_set, const void* parameter);
    char* (*predict)(const void* model, const Instance* instance);
    Hash_map_ptr (*predict_probability)(const void* model, const Instance* instance);
};

typedef struct model Model;

typedef Model *Model_ptr;

Detailed_classification_performance_ptr test_classifier(const Model* model, const Instance_list* test_set);

char* get_maximum(Array_list_ptr class_labels);

#endif //CLASSIFICATION_MODEL_H
