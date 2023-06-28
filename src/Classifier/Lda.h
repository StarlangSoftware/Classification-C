//
// Created by Olcay Taner YILDIZ on 26.06.2023.
//

#ifndef CLASSIFICATION_LDA_H
#define CLASSIFICATION_LDA_H

#include "Classifier.h"

Classifier_ptr train_lda(Instance_list_ptr train_set, const void* parameter);

Classifier_ptr load_lda(const char* file_name);

void free_lda(Classifier_ptr lda);

#endif //CLASSIFICATION_LDA_H
