//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#include <stdlib.h>
#include "ClassificationPerformance.h"

/**
 * A constructor that sets the accuracy and errorRate as 1 - accuracy via given accuracy.
 *
 * @param accuracy Double value input.
 */
Classification_performance_ptr create_classification_performance(double accuracy) {
    Classification_performance_ptr result = malloc(sizeof(Classification_performance));
    result->accuracy = accuracy;
    return result;
}
