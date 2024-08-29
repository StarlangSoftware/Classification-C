//
// Created by Olcay Taner YILDIZ on 13.07.2023.
//

#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Parameter/C45Parameter.h"
#include "../src/Model/Model.h"
#include "../src/Model/DecisionTree/DecisionTree.h"

void test_c45_classifier(Data_set_ptr data_set, double error_rate, int index, C45_parameter_ptr parameter){
    Model_ptr c45 = train_c45(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(c45, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in validation_c45 test %d %f\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_c45(c45);
}

int main(){
    create_datasets();
    C45_parameter_ptr parameter = create_c45_parameter(1, true, 0.2);
    test_c45_classifier(iris, 4.00, 1, parameter);
    test_c45_classifier(bupa, 22.61, 2, parameter);
    test_c45_classifier(dermatology, 2.46, 3, parameter);
    test_c45_classifier(car, 6.42, 4, parameter);
    test_c45_classifier(tictactoe, 10.97, 5, parameter);
    free_c45_parameter(parameter);
    free_datasets();
}