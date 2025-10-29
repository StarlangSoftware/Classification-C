//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Model/Model.h"
#include "../src/Model/DummyModel.h"

void test_dummy_classifier(Data_set_ptr data_set, double error_rate, int index){
    Model_ptr dummy = train_dummy(data_set->instances, NULL);
    Detailed_classification_performance_ptr performance = test_classifier(dummy, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in dummy test %d\n", index);
    }
    free_detailed_classification_performance(performance);
    free_dummy(dummy);
}

int main(){
    start_large_memory_check();
    create_datasets();
    test_dummy_classifier(iris, 66.67, 1);
    test_dummy_classifier(bupa, 42.03, 2);
    test_dummy_classifier(dermatology, 69.40, 3);
    test_dummy_classifier(car, 29.98, 4);
    test_dummy_classifier(tictactoe, 34.66, 5);
    free_datasets();
    end_memory_check();
}