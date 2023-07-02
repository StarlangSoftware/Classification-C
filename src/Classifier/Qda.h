//
// Created by Olcay Taner YILDIZ on 2.07.2023.
//

#ifndef CLASSIFICATION_QDA_H
#define CLASSIFICATION_QDA_H

#include "Classifier.h"
#include "../InstanceList/InstanceList.h"

Classifier_ptr train_qda(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_qda(const char* file_name);

void free_qda(Classifier_ptr qda);

#endif //CLASSIFICATION_QDA_H
