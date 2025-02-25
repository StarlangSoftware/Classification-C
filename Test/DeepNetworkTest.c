//
// Created by Olcay Taner YILDIZ on 21.07.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Model/Model.h"
#include "../src/Model/NeuralNetwork/DeepNetworkModel.h"

void test_deep_network_classifier(Data_set_ptr data_set, double error_rate, int index, Deep_network_parameter_ptr parameter){
    Model_ptr deep_network = train_deep_network(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(deep_network, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in deep network test %d %f\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_deep_network(deep_network);
}

int main(){
    create_datasets();
    Array_list_ptr hidden_nodes = create_array_list();
    array_list_add_int(hidden_nodes, 5);
    array_list_add_int(hidden_nodes, 5);
    Deep_network_parameter_ptr parameter = create_deep_network_parameter(1, 0.1, 0.99, 0.2, 100, hidden_nodes, SIGMOID);
    test_deep_network_classifier(iris, 6.0, 1, parameter);
    free_deep_network_parameter(parameter);
    hidden_nodes = create_array_list();
    array_list_add_int(hidden_nodes, 15);
    array_list_add_int(hidden_nodes, 15);
    parameter = create_deep_network_parameter(1, 0.01, 0.99, 0.2, 100, hidden_nodes, SIGMOID);
    test_deep_network_classifier(bupa, 28.70, 2, parameter);
    free_deep_network_parameter(parameter);
    hidden_nodes = create_array_list();
    array_list_add_int(hidden_nodes, 20);
    parameter = create_deep_network_parameter(1, 0.01, 0.99, 0.2, 100, hidden_nodes, SIGMOID);
    test_deep_network_classifier(dermatology, 1.91, 3, parameter);
    free_deep_network_parameter(parameter);
    free_datasets();
}