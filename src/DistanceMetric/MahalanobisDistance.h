//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_MAHALANOBISDISTANCE_H
#define CLASSIFICATION_MAHALANOBISDISTANCE_H

#include "../Instance/Instance.h"

double mahalanobis_distance(const Instance* instance1, const Instance* instance2, const void* parameter);

#endif //CLASSIFICATION_MAHALANOBISDISTANCE_H
