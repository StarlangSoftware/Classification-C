//
// Created by Olcay Taner YILDIZ on 29.08.2024.
//

#ifndef CLASSIFICATION_BAGGINGMODEL_H
#define CLASSIFICATION_BAGGINGMODEL_H

#include "../Model.h"

Model_ptr train_bagging(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_bagging(const char* file_name);

void free_bagging(Model_ptr bagging);

#endif //CLASSIFICATION_BAGGINGMODEL_H
