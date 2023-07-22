//
// Created by Olcay Taner YILDIZ on 22.07.2023.
//

#ifndef CLASSIFICATION_DISCRETETOINDEXED_H
#define CLASSIFICATION_DISCRETETOINDEXED_H

#include "../DataSet/DataSet.h"
#include "LaryFilter.h"

void convert_instance_discrete_to_indexed(Lary_filter_ptr lary_filter, Instance_ptr instance);

void convert_data_definition_discrete_to_indexed(Lary_filter_ptr lary_filter);

#endif //CLASSIFICATION_DISCRETETOINDEXED_H
