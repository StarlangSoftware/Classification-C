//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#ifndef CLASSIFICATION_STATISTICALTESTRESULT_H
#define CLASSIFICATION_STATISTICALTESTRESULT_H

#include <stdbool.h>
#include "StatisticalTestResultType.h"

struct statistical_test_result{
    double p_value;
    bool only_two_tailed;
};

typedef struct statistical_test_result Statistical_test_result;

typedef Statistical_test_result *Statistical_test_result_ptr;

Statistical_test_result_ptr create_statistical_test_result(double p_value, bool only_two_tailed);

Statistical_test_result_type one_tailed(Statistical_test_result_ptr result, double alpha);

Statistical_test_result_type two_tailed(Statistical_test_result_ptr result, double alpha);

#endif //CLASSIFICATION_STATISTICALTESTRESULT_H
