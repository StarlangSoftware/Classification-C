//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <math.h>
#include "Sign.h"

int factorial(int n) {
    int i, result = 1;
    for (i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}

int binomial(int m, int n) {
    if (n == 0 || m == n){
        return 1;
    }
    else {
        return factorial(m) / (factorial(n) * factorial(m - n));
    }
}

Statistical_test_result_ptr
compare_sign(const Experiment_performance *classifier1, const Experiment_performance *classifier2) {
    int plus = 0, minus = 0;
    for (int i = 0; i < number_of_experiments(classifier1); i++){
        if (get_error_rate(classifier1, i) < get_error_rate(classifier2, i)){
            plus++;
        } else {
            if (get_error_rate(classifier1, i) > get_error_rate(classifier2, i)){
                minus++;
            }
        }
    }
    int total = plus + minus;
    double pValue = 0.0;
    for (int i = 0; i <= plus; i++){
        pValue += binomial(total, i) / pow(2, total);
    }
    return create_statistical_test_result(pValue, false);
}
