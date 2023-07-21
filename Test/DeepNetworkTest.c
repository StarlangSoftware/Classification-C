//
// Created by Olcay Taner YILDIZ on 21.07.2023.
//

#include <math.h>
#include <stdlib.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/DeepNetwork.h"
#include "CreateDataSets.h"

void test_deep_network_classifier(Data_set_ptr data_set, double error_rate, int index, Deep_network_parameter_ptr parameter){
    Classifier_ptr deep_network = train_deep_network(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(deep_network, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in deep network test %d %f\n", index, 100 * performance->error_rate);
    }
    free_deep_network(deep_network);
}

int main(){
    create_datasets();
    Array_list_ptr hidden_nodes = create_array_list();
    int* value = malloc(sizeof(int));
    *value = 5;
    array_list_add(hidden_nodes, value);
    value = malloc(sizeof(int));
    *value = 5;
    array_list_add(hidden_nodes, value);
    Deep_network_parameter_ptr parameter = create_deep_network_parameter(1, 0.1, 0.99, 0.2, 100, hidden_nodes, SIGMOID);
    test_deep_network_classifier(iris, 6.0, 1, parameter);
    free_deep_network_parameter(parameter);
    hidden_nodes = create_array_list();
    value = malloc(sizeof(int));
    *value = 15;
    array_list_add(hidden_nodes, value);
    value = malloc(sizeof(int));
    *value = 15;
    array_list_add(hidden_nodes, value);
    parameter = create_deep_network_parameter(1, 0.01, 0.99, 0.2, 100, hidden_nodes, SIGMOID);
    test_deep_network_classifier(bupa, 28.70, 2, parameter);
    free_deep_network_parameter(parameter);
    hidden_nodes = create_array_list();
    value = malloc(sizeof(int));
    *value = 20;
    array_list_add(hidden_nodes, value);
    parameter = create_deep_network_parameter(1, 0.01, 0.99, 0.2, 100, hidden_nodes, SIGMOID);
    test_deep_network_classifier(dermatology, 1.91, 3, parameter);
    free_deep_network_parameter(parameter);
}