//
// Created by Olcay Taner YILDIZ on 29.08.2024.
//

#ifndef CLASSIFICATION_DECISIONSTUMP_H
#define CLASSIFICATION_DECISIONSTUMP_H

#include "../Model.h"
#include "../../InstanceList/InstanceList.h"

Model_ptr train_c45_stump(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_c45_stump(const char* file_name);

void free_c45_stump(Model_ptr c45_stump);

#endif //CLASSIFICATION_DECISIONSTUMP_H
