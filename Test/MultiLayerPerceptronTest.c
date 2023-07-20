//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/MultiLayerPerceptron.h"
#include "CreateDataSets.h"

void test_multi_layer_perceptron_classifier(Data_set_ptr data_set, double error_rate, int index, Multi_layer_perceptron_parameter_ptr parameter){
    Classifier_ptr multi_layer_perceptron = train_multi_layer_perceptron(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(multi_layer_perceptron, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in multi layer perceptron test %d %f\n", index, 100 * performance->error_rate);
    }
    free_multi_layer_perceptron(multi_layer_perceptron);
}

int main(){
    create_datasets();
    Multi_layer_perceptron_parameter_ptr parameter = create_multi_layer_perceptron_parameter_ptr(1, 0.1, 0.99, 0.2, 100, 3, SIGMOID);
    test_multi_layer_perceptron_classifier(iris, 1.33, 1, parameter);
    free_multi_layer_perceptron_parameter_ptr(parameter);
    parameter = create_multi_layer_perceptron_parameter_ptr(1, 0.01, 0.99, 0.2, 100, 30, SIGMOID);
    test_multi_layer_perceptron_classifier(bupa, 28.99, 2, parameter);
    free_multi_layer_perceptron_parameter_ptr(parameter);
    parameter = create_multi_layer_perceptron_parameter_ptr(1, 0.01, 0.99, 0.2, 100, 20, SIGMOID);
    test_multi_layer_perceptron_classifier(dermatology, 1.91, 3, parameter);
    free_multi_layer_perceptron_parameter_ptr(parameter);
}