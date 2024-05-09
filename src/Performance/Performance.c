//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "Performance.h"

/**
 * Constructor that sets the error rate.
 *
 * @param errorRate Double input.
 */
Performance_ptr create_performance(double error_rate) {
    Performance_ptr result = malloc_(sizeof(Performance), "create_performance");
    result->error_rate = error_rate;
    return result;
}

/**
 * Frees memory allocated for performance
 * @param performance Performance
 */
void free_performance(Performance_ptr performance) {
    free_(performance);
}
