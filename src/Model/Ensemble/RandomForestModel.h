//
// Created by Olcay Taner YILDIZ on 29.08.2024.
//

#ifndef CLASSIFICATION_RANDOMFORESTMODEL_H
#define CLASSIFICATION_RANDOMFORESTMODEL_H

#include "../Model.h"
#include "../../InstanceList/InstanceList.h"

Model_ptr train_random_forest(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_random_forest(const char* file_name);

void free_random_forest(Model_ptr random_forest);

#endif //CLASSIFICATION_RANDOMFORESTMODEL_H
