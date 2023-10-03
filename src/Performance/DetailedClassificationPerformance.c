//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#include <stdlib.h>
#include "DetailedClassificationPerformance.h"

/**
 * A constructor that  sets the accuracy and errorRate as 1 - accuracy via given ConfusionMatrix and also sets the confusionMatrix.
 *
 * @param confusionMatrix ConfusionMatrix input.
 */
Detailed_classification_performance_ptr
create_detailed_classification_performance(Confusion_matrix_ptr confusion_matrix) {
    Detailed_classification_performance_ptr result = malloc(sizeof(Detailed_classification_performance));
    result->confusion_matrix = confusion_matrix;
    result->accuracy = get_accuracy(confusion_matrix);
    result->error_rate = 1 - result->accuracy;
    return result;
}

void
free_detailed_classification_performance(Detailed_classification_performance_ptr detailed_classification_performance) {
    free_confusion_matrix(detailed_classification_performance->confusion_matrix);
    free(detailed_classification_performance);
}
