//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "CreateDataSets.h"
#include "../src/Classifier/RandomForest.h"
#include "../src/Parameter/RandomForestParameter.h"

void test_random_forest_classifier(Data_set_ptr data_set, double error_rate, int index, Random_forest_parameter_ptr parameter){
    Classifier_ptr random_forest = train_random_forest(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(random_forest, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in random forest test %d %f\n", index, 100 * performance->error_rate);
    }
    free_random_forest(random_forest);
}

int main(){
    create_datasets();
    Random_forest_parameter_ptr parameter = create_random_forest_parameter(1, 100, 35);
    test_random_forest_classifier(iris, 0.00, 1, parameter);
    test_random_forest_classifier(bupa, 0.00, 2, parameter);
    test_random_forest_classifier(dermatology, 0.00, 3, parameter);
    test_random_forest_classifier(car, 0.00, 4, parameter);
    test_random_forest_classifier(tictactoe, 0.00, 5, parameter);
    free_random_forest_parameter(parameter);
}