//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "StatisticalTestResult.h"

Statistical_test_result_ptr create_statistical_test_result(double p_value, bool only_two_tailed) {
    Statistical_test_result_ptr result = malloc_(sizeof(Statistical_test_result), "create_statistical_test_result");
    result->p_value = p_value;
    result->only_two_tailed = only_two_tailed;
    return result;
}

Statistical_test_result_type one_tailed(Statistical_test_result_ptr result, double alpha) {
    if (result->p_value < alpha){
        return REJECT;
    } else {
        return FAILED_TO_REJECT;
    }
}

Statistical_test_result_type two_tailed(Statistical_test_result_ptr result, double alpha) {
    if (result->only_two_tailed){
        if (result->p_value < alpha){
            return REJECT;
        } else {
            return FAILED_TO_REJECT;
        }
    } else {
        if (result->p_value < alpha / 2 || result->p_value > 1 - alpha / 2){
            return REJECT;
        } else {
            return FAILED_TO_REJECT;
        }
    }
}
