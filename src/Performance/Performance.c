//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#include <stdlib.h>
#include "Performance.h"

/**
 * Constructor that sets the error rate.
 *
 * @param errorRate Double input.
 */
Performance_ptr create_performance(double error_rate) {
    Performance_ptr result = malloc(sizeof(Performance));
    result->error_rate = error_rate;
    return result;
}

void free_performance(Performance_ptr performance) {
    free(performance);
}
