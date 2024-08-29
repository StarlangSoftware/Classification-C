//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#ifndef CLASSIFICATION_NAIVEBAYESMODEL_H
#define CLASSIFICATION_NAIVEBAYESMODEL_H

#include <DiscreteDistribution.h>
#include "../../Instance/Instance.h"
#include "../Model.h"
#include "../../InstanceList/Partition.h"

struct naive_bayes_model{
    Discrete_distribution_ptr prior_distribution;
    Hash_map_ptr class_means;
    Hash_map_ptr class_deviations;
};

typedef struct naive_bayes_model Naive_bayes_model;

typedef Naive_bayes_model *Naive_bayes_model_ptr;

Naive_bayes_model_ptr create_naive_bayes_model(Discrete_distribution_ptr prior_distribution,
                                               Hash_map_ptr class_means,
                                               Hash_map_ptr class_deviations);

Naive_bayes_model_ptr create_naive_bayes_model2(const char* file_name);

double log_likelihood_continuous(const Naive_bayes_model* model, const char* class_label, const Instance* instance);

char *predict_naive_bayes(const void *model, const Instance* instance);

void free_naive_bayes_model(Naive_bayes_model_ptr model);

Model_ptr train_naive_bayes(Instance_list_ptr train_set, const void* parameter);

Model_ptr load_naive_bayes(const char* file_name);

void free_naive_bayes(Model_ptr naive_bayes);

void train_continuous_version(Model_ptr classifier, Discrete_distribution_ptr prior_distribution, Partition_ptr class_lists);

#endif //CLASSIFICATION_NAIVEBAYESMODEL_H
