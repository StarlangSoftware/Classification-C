//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#ifndef CLASSIFICATION_DUMMY_H
#define CLASSIFICATION_DUMMY_H

#include "Classifier.h"
#include "../InstanceList/InstanceList.h"
#include "../Performance/DetailedClassificationPerformance.h"

Classifier_ptr train_dummy(Instance_list_ptr train_set, void* parameter);

Classifier_ptr load_dummy(char* file_name);

Detailed_classification_performance_ptr test_dummy(Classifier_ptr dummy, Instance_list_ptr test_set);

void free_dummy(Classifier_ptr dummy);

#endif //CLASSIFICATION_DUMMY_H
