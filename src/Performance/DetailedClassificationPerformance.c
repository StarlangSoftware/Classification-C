//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#include <Memory/Memory.h>
#include "DetailedClassificationPerformance.h"

/**
 * A constructor that  sets the accuracy and errorRate as 1 - accuracy via given ConfusionMatrix and also sets the confusionMatrix.
 *
 * @param confusion_matrix ConfusionMatrix input.
 */
Detailed_classification_performance_ptr
create_detailed_classification_performance(Confusion_matrix_ptr confusion_matrix) {
    Detailed_classification_performance_ptr result = malloc_(sizeof(Detailed_classification_performance), "create_detailed_classification_performance");
    result->confusion_matrix = confusion_matrix;
    result->accuracy = get_accuracy(confusion_matrix);
    result->error_rate = 1 - result->accuracy;
    return result;
}

/**
 * Frees memory allocated for detailed classification performance
 * @param detailed_classification_performance Detailed classification performance
 */
void
free_detailed_classification_performance(Detailed_classification_performance_ptr detailed_classification_performance) {
    free_confusion_matrix(detailed_classification_performance->confusion_matrix);
    free_(detailed_classification_performance);
}
