//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/Bagging.h"
#include "CreateDataSets.h"
#include "../src/Parameter/BaggingParameter.h"

void test_random_forest_classifier(Data_set_ptr data_set, double error_rate, int index, Bagging_parameter_ptr parameter){
    Classifier_ptr bagging = train_bagging(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(bagging, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in bagging test %d %f\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_bagging(bagging);
}

int main(){
    create_datasets();
    Bagging_parameter_ptr parameter = create_bagging_parameter(1, 100);
    test_random_forest_classifier(iris, 0.00, 1, parameter);
    test_random_forest_classifier(bupa, 0.00, 2, parameter);
    test_random_forest_classifier(dermatology, 0.00, 3, parameter);
    test_random_forest_classifier(car, 0.00, 4, parameter);
    test_random_forest_classifier(tictactoe, 0.00, 5, parameter);
    free_bagging_parameter(parameter);
    free_datasets();
}