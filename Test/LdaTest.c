//
// Created by Olcay Taner YILDIZ on 27.06.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Performance/DetailedClassificationPerformance.h"
#include "../src/Model/Parametric/LdaModel.h"

void test_lda_classifier(Data_set_ptr data_set, double error_rate, int index){

    Model_ptr lda = train_lda(data_set->instances, NULL);
    Detailed_classification_performance_ptr performance = test_classifier(lda, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in lda test %d %.2lf\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_lda(lda);
}

int main(){
    start_large_memory_check();
    create_datasets();
    test_lda_classifier(iris, 2.00, 1);
    test_lda_classifier(bupa, 29.57, 2);
    test_lda_classifier(dermatology, 1.91, 3);
    free_datasets();
    end_memory_check();
}
