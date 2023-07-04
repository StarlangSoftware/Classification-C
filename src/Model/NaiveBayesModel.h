//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#ifndef CLASSIFICATION_NAIVEBAYESMODEL_H
#define CLASSIFICATION_NAIVEBAYESMODEL_H

#include <DiscreteDistribution.h>
#include "../Instance/Instance.h"

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

#endif //CLASSIFICATION_NAIVEBAYESMODEL_H
