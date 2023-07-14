//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#ifndef CLASSIFICATION_TREEENSEMBLEMODEL_H
#define CLASSIFICATION_TREEENSEMBLEMODEL_H

#include <ArrayList.h>
#include <stdio.h>
#include <HashMap/HashMap.h>
#include "../Instance/Instance.h"

struct tree_ensemble_model{
    Array_list_ptr forest;
};

typedef struct tree_ensemble_model Tree_ensemble_model;

typedef Tree_ensemble_model *Tree_ensemble_model_ptr;

Tree_ensemble_model_ptr create_tree_ensemble_model(Array_list_ptr forest);

Tree_ensemble_model_ptr create_tree_ensemble_model2(const char* file_name);

void free_tree_ensemble_model(Tree_ensemble_model_ptr model);

char* predict_ensemble(const void *model, const Instance *instance);

Hash_map_ptr predict_probability_ensemble(const void *model, const Instance* instance);

#endif //CLASSIFICATION_TREEENSEMBLEMODEL_H
