//
// Created by Olcay Taner YILDIZ on 22.06.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Model/Model.h"
#include "../src/Model/RandomModel.h"

void test_random_classifier(Data_set_ptr data_set, double error_rate, int index){
    Model_ptr random = train_random(data_set->instances, NULL);
    Detailed_classification_performance_ptr performance = test_classifier(random, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in random test %d\n", index);
    }
    free_detailed_classification_performance(performance);
    free_random(random);
}

int main(){
    start_large_memory_check();
    create_datasets();
    test_random_classifier(iris, 69.33, 1);
    test_random_classifier(bupa, 49.27, 2);
    test_random_classifier(dermatology, 85.25, 3);
    test_random_classifier(car, 75.17, 4);
    test_random_classifier(tictactoe, 46.76, 5);
    free_datasets();
    end_memory_check();
}