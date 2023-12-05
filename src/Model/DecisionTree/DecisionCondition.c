//
// Created by Olcay Taner YILDIZ on 8.07.2023.
//

#include <stdlib.h>
#include <FileUtils.h>
#include <string.h>
#include <Memory/Memory.h>
#include "DecisionCondition.h"

/**
 * A constructor that sets attributeIndex and Attribute value. It also assigns equal sign to the comparison character.
 *
 * @param attributeIndex Integer number that shows attribute index.
 * @param value          The value of the Attribute.
 */
Decision_condition_ptr create_decision_condition(int attribute_index, Attribute_ptr value) {
    Decision_condition_ptr result = malloc_(sizeof(Decision_condition), "create_decision_condition");
    result->attribute_index = attribute_index;
    result->comparison = '=';
    result->value = value;
    return result;
}

/**
 * A constructor that sets attributeIndex, comparison and Attribute value.
 *
 * @param attributeIndex Integer number that shows attribute index.
 * @param value          The value of the Attribute.
 * @param comparison     Comparison character.
 */
Decision_condition_ptr create_decision_condition2(int attribute_index, char comparison, Attribute_ptr value) {
    Decision_condition_ptr result = malloc_(sizeof(Decision_condition), "create_decision_condition2");
    result->attribute_index = attribute_index;
    result->comparison = comparison;
    result->value = value;
    return result;
}

Decision_condition_ptr create_decision_condition3(FILE *input_file) {
    char type[MAX_LINE_LENGTH];
    Decision_condition_ptr result = malloc_(sizeof(Decision_condition), "create_decision_condition3");
    fscanf(input_file, "%d %c %s", &(result->attribute_index), &(result->comparison), type);
    if (result->attribute_index != -1){
        if (result->comparison == '='){
            result->value = create_discrete_attribute(type);
        } else {
            if (result->comparison == ':'){
                result->comparison = '=';
                int maxIndex;
                fscanf(input_file, "%d", &maxIndex);
                result->value = create_discrete_indexed_attribute(atoi(type), maxIndex);
            } else {
                result->value = create_continuous_attribute(atof(type));
            }
        }
    }
    return result;
}

void free_decision_condition(Decision_condition_ptr decision_condition) {
    if (decision_condition->value != NULL){
        free_attribute(decision_condition->value);
    }
    free_(decision_condition);
}

/**
 * The satisfy method takes an Instance as an input.
 * <p>
 * If defined Attribute value is a DiscreteIndexedAttribute it compares the index of Attribute of instance at the
 * attributeIndex and the index of Attribute value and returns the result.
 * <p>
 * If defined Attribute value is a DiscreteAttribute it compares the value of Attribute of instance at the
 * attributeIndex and the value of Attribute value and returns the result.
 * <p>
 * If defined Attribute value is a ContinuousAttribute it compares the value of Attribute of instance at the
 * attributeIndex and the value of Attribute value and returns the result according to the comparison character whether it is
 * less than or greater than signs.
 *
 * @param instance Instance to compare.
 * @return True if gicen instance satisfies the conditions.
 */
bool satisfy(Decision_condition_ptr decision_condition, const Instance *instance) {
    Attribute_ptr instance_attribute = get_attribute(instance, decision_condition->attribute_index);
    if (is_discrete_indexed(decision_condition->value)){
        if (decision_condition->value->int_value != -1){
            return instance_attribute->int_value == decision_condition->value->int_value;
        } else {
            return true;
        }
    } else {
        if (is_discrete(decision_condition->value)){
            return strcmp(instance_attribute->string_value, decision_condition->value->string_value) == 0;
        } else {
            if (is_continuous(decision_condition->value)){
                if (decision_condition->comparison == '<'){
                    return instance_attribute->float_value <= decision_condition->value->float_value;
                } else{
                    if (decision_condition->comparison == '>'){
                        return instance_attribute->float_value > decision_condition->value->float_value;
                    }
                }
            }
        }
    }
    return false;
}

Decision_condition_ptr create_decision_condition4() {
    Decision_condition_ptr result = malloc_(sizeof(Decision_condition), "create_decision_condition4");
    result->attribute_index = -1;
    result->comparison = ' ';
    result->value = NULL;
    return result;
}
