//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#ifndef CLASSIFICATION_NAIVEBAYES_H
#define CLASSIFICATION_NAIVEBAYES_H

#include "Classifier.h"
#include "../InstanceList/Partition.h"

Classifier_ptr train_naive_bayes(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_naive_bayes(const char* file_name);

void free_naive_bayes(Classifier_ptr naive_bayes);

void train_continuous_version(Classifier_ptr classifier, Discrete_distribution_ptr prior_distribution, Partition_ptr class_lists);

#endif //CLASSIFICATION_NAIVEBAYES_H
