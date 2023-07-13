//
// Created by Olcay Taner YILDIZ on 8.07.2023.
//

#ifndef CLASSIFICATION_DECISIONCONDITION_H
#define CLASSIFICATION_DECISIONCONDITION_H

#include <stdio.h>
#include "../../Attribute/Attribute.h"
#include "../../Instance/Instance.h"

struct decision_condition{
    int attribute_index;
    char comparison;
    Attribute_ptr value;
};

typedef struct decision_condition Decision_condition;

typedef Decision_condition *Decision_condition_ptr;

Decision_condition_ptr create_decision_condition(int attribute_index, Attribute_ptr value);

Decision_condition_ptr create_decision_condition2(int attribute_index, char comparison, Attribute_ptr value);

Decision_condition_ptr create_decision_condition3(FILE* input_file);

Decision_condition_ptr create_decision_condition4();

void free_decision_condition(Decision_condition_ptr decision_condition);

bool satisfy(Decision_condition_ptr decision_condition, const Instance *instance);

#endif //CLASSIFICATION_DECISIONCONDITION_H
