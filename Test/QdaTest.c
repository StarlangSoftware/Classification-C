//
// Created by Olcay Taner YILDIZ on 2.07.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Performance/DetailedClassificationPerformance.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/Qda.h"
#include "CreateDataSets.h"

void test_qda_classifier(Data_set_ptr data_set, double error_rate, int index){

    Classifier_ptr qda = train_qda(data_set->instances, NULL);
    Detailed_classification_performance_ptr performance = test_classifier(qda, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in lda test %d %.2lf\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_qda(qda);
}

int main(){
    create_datasets();
    test_qda_classifier(iris, 2.00, 1);
    test_qda_classifier(bupa, 36.52, 2);
    free_datasets();
}