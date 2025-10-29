//
// Created by Olcay Taner YILDIZ on 13.07.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Performance/DetailedClassificationPerformance.h"
#include "../src/Model/Model.h"
#include "../src/Model/DecisionTree/DecisionStump.h"

void test_c45_stump_classifier(Data_set_ptr data_set, double error_rate, int index){
    Model_ptr c45 = train_c45_stump(data_set->instances, NULL);
    Detailed_classification_performance_ptr performance = test_classifier(c45, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in validation_c45 stump test %d %f\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_c45_stump(c45);
}

int main(){
    start_large_memory_check();
    create_datasets();
    test_c45_stump_classifier(iris, 33.33, 1);
    test_c45_stump_classifier(bupa, 36.81, 2);
    test_c45_stump_classifier(car, 29.98, 4);
    test_c45_stump_classifier(dermatology, 49.73, 3);
    test_c45_stump_classifier(tictactoe, 30.06, 5);
    free_datasets();
    end_memory_check();
}
