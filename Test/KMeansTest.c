//
// Created by Olcay Taner YILDIZ on 24.06.2023.
//

#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/KMeans.h"
#include "CreateDataSets.h"
#include "../src/Parameter/KMeansParameter.h"

void test_kmeans_classifier(Data_set_ptr data_set, double error_rate, int index, K_means_parameter_ptr parameter){

    Classifier_ptr k_means = train_k_means(data_set->instances, parameter);
    Detailed_classification_performance_ptr performance = test_classifier(k_means, data_set->instances);
    if (fabs(performance->error_rate * 100.0 - error_rate) > 0.01){
        printf("Error in kmeans test %d %.2lf\n", index, 100 * performance->error_rate);
    }
    free_k_means(k_means);
}

int main(){
    create_datasets();
    K_means_parameter_ptr parameter = create_k_means_parameter2(1);
    test_kmeans_classifier(iris, 7.33, 1, parameter);
    test_kmeans_classifier(bupa, 43.77, 2, parameter);
    test_kmeans_classifier(dermatology, 45.08, 3, parameter);
    test_kmeans_classifier(car, 44.21, 4, parameter);
    test_kmeans_classifier(tictactoe, 38.94, 5, parameter);
    test_kmeans_classifier(nursery, 63.66, 6, parameter);
    test_kmeans_classifier(chess, 83.25, 7, parameter);
}