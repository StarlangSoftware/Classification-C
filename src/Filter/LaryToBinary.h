//
// Created by Olcay Taner YILDIZ on 22.07.2023.
//

#ifndef CLASSIFICATION_LARYTOBINARY_H
#define CLASSIFICATION_LARYTOBINARY_H

#include "../DataSet/DataSet.h"
#include "LaryFilter.h"

void convert_instance_lary_to_binary(Lary_filter_ptr lary_filter, Instance_ptr instance);

void convert_data_definition_lary_to_binary(Lary_filter_ptr lary_filter);

#endif //CLASSIFICATION_LARYTOBINARY_H
