//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#include <Matrix.h>
#include "MahalanobisDistance.h"

/**
 * Calculates Mahalanobis distance between two instances. (x^(1) - x^(2)) S (x^(1) - x^(2))^T
 *
 * @param instance1 First instance.
 * @param instance2 Second instance.
 * @return Mahalanobis distance between two instances.
 */
double mahalanobis_distance(const Instance* instance1, const Instance* instance2, const void *parameter) {
    Vector_ptr v1 = to_vector(instance1);
    Vector_ptr v2 = to_vector(instance2);
    subtract_vector(v1, v2);
    Matrix_ptr covariance_inverse = (Matrix_ptr) parameter;
    Vector_ptr v3 = multiply_with_vector_from_left(covariance_inverse, v1);
    return dot_product(v3, v1);
}
