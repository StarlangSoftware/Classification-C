//
// Created by Olcay Taner YILDIZ on 15.07.2023.
//

#include <Memory/Memory.h>
#include "StatisticalTestResult.h"

/**
 * Constructor of the StatisticalTestResult. It sets the attribute values.
 * @param p_value p value of the statistical test result
 * @param only_two_tailed True, if this test applicable only two tailed tests, false otherwise.
 */
Statistical_test_result_ptr create_statistical_test_result(double p_value, bool only_two_tailed) {
    Statistical_test_result_ptr result = malloc_(sizeof(Statistical_test_result));
    result->p_value = p_value;
    result->only_two_tailed = only_two_tailed;
    return result;
}

/**
 * Returns reject or failed to reject, depending on the alpha level and p value of the statistical test that checks
 * one tailed null hypothesis such as mu1 < mu2. If p value is less than the alpha level, the test rejects the null
 * hypothesis. Otherwise, it fails to reject the null hypothesis.
 * @param result Current statistical result
 * @param alpha Alpha level of the test
 * @return If p value is less than the alpha level, the test rejects the null hypothesis. Otherwise, it fails to
 * reject the null hypothesis.
 */
Statistical_test_result_type one_tailed(Statistical_test_result_ptr result, double alpha) {
    if (result->p_value < alpha){
        return REJECT;
    } else {
        return FAILED_TO_REJECT;
    }
}

/**
 * Returns reject or failed to reject, depending on the alpha level and p value of the statistical test that checks
 * one tailed null hypothesis such as mu1 < mu2 or two tailed null hypothesis such as mu1 = mu2. If the null
 * hypothesis is two tailed, and p value is less than the alpha level, the test rejects the null hypothesis.
 * Otherwise, it fails to reject the null hypothesis. If the null  hypothesis is one tailed, and p value is less
 * than alpha / 2 or p value is larger than 1 - alpha / 2, the test  rejects the null  hypothesis. Otherwise, it
 * fails to reject the null hypothesis.
 * @param result Current statistical result
 * @param alpha Alpha level of the test
 * @return If the null  hypothesis is two tailed, and p value is less than the alpha level, the test rejects the
 * null hypothesis.  Otherwise, it fails to reject the null hypothesis. If the null  hypothesis is one tailed, and
 * p value is less  than alpha / 2 or p value is larger than 1 - alpha / 2, the test  rejects the null  hypothesis.
 * Otherwise, it  fails to reject the null hypothesis.
 */
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
