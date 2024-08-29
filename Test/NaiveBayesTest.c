//
// Created by Olcay Taner YILDIZ on 4.07.2023.
//

#include <math.h>
#include <Memory/Memory.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"
#include "../src/Model/Parametric/NaiveBayesModel.h"

void test_naive_bayes_classifier(Data_set_ptr data_set, double error_rate, int index){

    Model_ptr naive_bayes = train_naive_bayes(data_set->instances, NULL);
    Detailed_classification_performance_ptr performance = test_classifier(naive_bayes, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in naive bayes test %d %.2lf\n", index, 100 * performance->error_rate);
    }
    free_detailed_classification_performance(performance);
    free_naive_bayes(naive_bayes);
}

int main(){
    create_datasets();
    test_naive_bayes_classifier(iris, 4.00, 1);
    test_naive_bayes_classifier(bupa, 38.26, 2);
    test_naive_bayes_classifier(dermatology, 69.40, 3);
    free_datasets();
}