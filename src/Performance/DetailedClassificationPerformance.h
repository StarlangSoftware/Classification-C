//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#ifndef CLASSIFICATION_DETAILEDCLASSIFICATIONPERFORMANCE_H
#define CLASSIFICATION_DETAILEDCLASSIFICATIONPERFORMANCE_H

#include "ConfusionMatrix.h"

struct detailed_classification_performance{
    Confusion_matrix_ptr confusion_matrix;
    double error_rate;
    double accuracy;
};

typedef struct detailed_classification_performance Detailed_classification_performance;

typedef Detailed_classification_performance* Detailed_classification_performance_ptr;

Detailed_classification_performance_ptr create_detailed_classification_performance(Confusion_matrix_ptr confusion_matrix);

void free_detailed_classification_performance(Detailed_classification_performance_ptr detailed_classification_performance);

#endif //CLASSIFICATION_DETAILEDCLASSIFICATIONPERFORMANCE_H
