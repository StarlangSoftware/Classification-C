//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include "EuclidianDistance.h"
#include <string.h>
#include <math.h>

/**
 * Calculates Euclidian distance between two instances. For continuous features: \sum_{i=1}^d (x_i^(1) - x_i^(2))^2,
 * For discrete features: \sum_{i=1}^d 1(x_i^(1) == x_i^(2))
 *
 * @param instance1 First instance
 * @param instance2 Second instance
 * @return Euclidian distance between two instances.
 */
double euclidian_distance(const Instance* instance1, const Instance* instance2, const void* parameter) {
    double result = 0;
    for (int i = 0; i < attribute_size(instance1); i++) {
        if (is_discrete(get_attribute(instance1, i)) && is_discrete(get_attribute(instance2, i))) {
            if (strcmp(get_attribute(instance1, i)->string_value, get_attribute(instance2, i)->string_value) != 0) {
                result += 1;
            }
        } else {
            if (is_continuous(get_attribute(instance1, i)) && is_continuous(get_attribute(instance2, i))) {
                result += pow(get_attribute(instance1, i)->float_value - get_attribute(instance2, i)->float_value, 2);
            }
        }
    }
    return result;
}
