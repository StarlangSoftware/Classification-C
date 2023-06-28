//
// Created by Olcay Taner YILDIZ on 26.06.2023.
//

#ifndef CLASSIFICATION_LDAMODEL_H
#define CLASSIFICATION_LDAMODEL_H

#include <DiscreteDistribution.h>
#include "../Instance/Instance.h"

struct lda_model{
    Discrete_distribution_ptr prior_distribution;
    Hash_map_ptr w0;
    Hash_map_ptr w;
};

typedef struct lda_model Lda_model;

typedef Lda_model *Lda_model_ptr;

Lda_model_ptr create_lda_model(Discrete_distribution_ptr prior_distribution, Hash_map_ptr w, Hash_map_ptr w0);

Lda_model_ptr create_lda_model2(const char* file_name);

void free_lda_model(Lda_model_ptr lda_model);

double calculate_metric_lda(const Lda_model * lda_model, const Instance* instance, const char* C_i);

char* predict_lda(const void* model, const Instance* instance);

#endif //CLASSIFICATION_LDAMODEL_H
