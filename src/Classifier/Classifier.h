//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#ifndef CLASSIFICATION_CLASSIFIER_H
#define CLASSIFICATION_CLASSIFIER_H

#include <HashMap/HashMap.h>
#include "../Instance/Instance.h"
#include "../Performance/DetailedClassificationPerformance.h"
#include "../InstanceList/InstanceList.h"

struct classifier{
    void* model;
    struct classifier* (*train)(Instance_list_ptr train_set, const void* parameter);
    char* (*predict)(const void* model, const Instance* instance);
    Hash_map_ptr (*predict_probability)(const void* model, const Instance* instance);
};

typedef struct classifier Classifier;

typedef Classifier *Classifier_ptr;

Detailed_classification_performance_ptr test_classifier(const Classifier* classifier, const Instance_list* test_set);

char* get_maximum(Array_list_ptr class_labels);

#endif //CLASSIFICATION_CLASSIFIER_H
