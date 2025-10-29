//
// Created by Olcay Taner YILDIZ on 25.06.2023.
//

#include <math.h>
#include <Memory/Memory.h>

#include "../src/DataSet/DataSet.h"
#include "../src/Parameter/KnnParameter.h"
#include "CreateDataSets.h"
#include "../src/Model/Model.h"
#include "../src/Model/NonParametric/KnnModel.h"

void test_knn_classifier(Data_set_ptr data_set, double error_rate, int index, Knn_parameter_ptr parameter){

    Model_ptr knn = train_knn(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(knn, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in knn test %d %.2lf\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_knn(knn);
}

int main(){
    start_large_memory_check();
    create_datasets();
    Knn_parameter_ptr parameter = create_knn_parameter2(1, 3);
    test_knn_classifier(iris, 4.00, 1, parameter);
    test_knn_classifier(bupa, 19.42, 2, parameter);
    test_knn_classifier(dermatology, 3.55, 3, parameter);
    test_knn_classifier(car, 20.31, 4, parameter);
    test_knn_classifier(tictactoe, 32.57, 5, parameter);
    free_datasets();
    free_knn_parameter(parameter);
    end_memory_check();
}