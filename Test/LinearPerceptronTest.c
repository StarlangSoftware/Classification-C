//
// Created by Olcay Taner YILDIZ on 18.07.2023.
//

#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/LinearPerceptron.h"
#include "CreateDataSets.h"

void test_linear_perceptron_classifier(Data_set_ptr data_set, double error_rate, int index, Linear_perceptron_parameter_ptr parameter){
    Classifier_ptr linear_perceptron = train_linear_perceptron(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(linear_perceptron, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in linear perceptron test %d %f\n", index, 100 * performance->error_rate);
    }
    free_linear_perceptron(linear_perceptron);
}

int main(){
    create_datasets();
    Linear_perceptron_parameter_ptr parameter = create_linear_perceptron_parameter(1, 0.1, 0.99, 0.2, 100);
    test_linear_perceptron_classifier(iris, 2.00, 1, parameter);
    free_linear_perceptron_parameter(parameter);
    parameter = create_linear_perceptron_parameter(1, 0.001, 0.99, 0.2, 100);
    test_linear_perceptron_classifier(bupa, 30.72, 2, parameter);
    free_linear_perceptron_parameter(parameter);
    parameter = create_linear_perceptron_parameter(1, 0.01, 0.99, 0.2, 100);
    test_linear_perceptron_classifier(dermatology, 2.46, 3, parameter);
    free_linear_perceptron_parameter(parameter);
}