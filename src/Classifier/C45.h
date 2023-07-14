//
// Created by Olcay Taner YILDIZ on 10.07.2023.
//

#ifndef CLASSIFICATION_C45_H
#define CLASSIFICATION_C45_H

#include "Classifier.h"
#include "../InstanceList/InstanceList.h"
#include "../Model/DecisionTree/DecisionTree.h"

Classifier_ptr train_c45(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_c45(const char* file_name);

Classifier_ptr validation_c45(Decision_tree_ptr decision_tree);

void free_c45(Classifier_ptr c45);

#endif //CLASSIFICATION_C45_H
