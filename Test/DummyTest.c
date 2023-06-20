//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#include <stdlib.h>
#include <math.h>
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Classifier.h"
#include "../src/Classifier/Dummy.h"

Data_set_ptr iris, car, chess, bupa, tictactoe, dermatology, nursery;

void create_datasets(){
    Array_list_ptr attribute_types = create_array_list();
    for (int i = 0; i < 4; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        *type = CONTINUOUS;
        array_list_add(attribute_types, type);
    }
    Data_definition_ptr data_definition = create_data_definition2(attribute_types);
    iris = create_data_set4(data_definition, ",", "datasets/iris.data");
    attribute_types = create_array_list();
    for (int i = 0; i < 6; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        *type = CONTINUOUS;
        array_list_add(attribute_types, type);
    }
    data_definition = create_data_definition2(attribute_types);
    bupa = create_data_set4(data_definition, ",", "datasets/bupa.data");
    attribute_types = create_array_list();
    for (int i = 0; i < 34; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        *type = CONTINUOUS;
        array_list_add(attribute_types, type);
    }
    data_definition = create_data_definition2(attribute_types);
    dermatology = create_data_set4(data_definition, ",", "datasets/dermatology.data");
    attribute_types = create_array_list();
    for (int i = 0; i < 6; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        *type = DISCRETE;
        array_list_add(attribute_types, type);
    }
    data_definition = create_data_definition2(attribute_types);
    car = create_data_set4(data_definition, ",", "datasets/car.data");
    attribute_types = create_array_list();
    for (int i = 0; i < 9; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        *type = DISCRETE;
        array_list_add(attribute_types, type);
    }
    data_definition = create_data_definition2(attribute_types);
    tictactoe = create_data_set4(data_definition, ",", "datasets/tictactoe.data");
    attribute_types = create_array_list();
    for (int i = 0; i < 8; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        *type = DISCRETE;
        array_list_add(attribute_types, type);
    }
    data_definition = create_data_definition2(attribute_types);
    nursery = create_data_set4(data_definition, ",", "datasets/nursery.data");
    attribute_types = create_array_list();
    for (int i = 0; i < 6; i++){
        Attribute_type * type = malloc(sizeof(Attribute_type));
        if (i % 2 == 0){
            *type = DISCRETE;
        } else {
            *type = CONTINUOUS;
        }
        array_list_add(attribute_types, type);
    }
    data_definition = create_data_definition2(attribute_types);
    chess = create_data_set4(data_definition, ",", "datasets/chess.data");
}

int main(){
    create_datasets();
    Classifier_ptr dummy = train_dummy(iris->instances, NULL);
    Detailed_classification_performance_ptr performance = test_dummy(dummy, iris->instances);
    if (fabs(performance->error_rate * 100.0 - 66.67) > 0.01){
        printf("Error in dummy test 1\n");
    }
    dummy = train_dummy(bupa->instances, NULL);
    performance = test_dummy(dummy, bupa->instances);
    if (fabs(performance->error_rate * 100.0 - 42.03) > 0.01){
        printf("Error in dummy test 2\n");
    }
    dummy = train_dummy(dermatology->instances, NULL);
    performance = test_dummy(dummy, dermatology->instances);
    if (fabs(performance->error_rate * 100.0 - 69.40) > 0.01){
        printf("Error in dummy test 3\n");
    }
    dummy = train_dummy(car->instances, NULL);
    performance = test_dummy(dummy, car->instances);
    if (fabs(performance->error_rate * 100.0 - 29.98) > 0.01){
        printf("Error in dummy test 4\n");
    }
    dummy = train_dummy(tictactoe->instances, NULL);
    performance = test_dummy(dummy, tictactoe->instances);
    if (fabs(performance->error_rate * 100.0 - 34.66) > 0.01){
        printf("Error in dummy test 5\n");
    }
    dummy = train_dummy(nursery->instances, NULL);
    performance = test_dummy(dummy, nursery->instances);
    if (fabs(performance->error_rate * 100.0 - 66.67) > 0.01){
        printf("Error in dummy test 6\n");
    }
    dummy = train_dummy(chess->instances, NULL);
    performance = test_dummy(dummy, chess->instances);
    if (fabs(performance->error_rate * 100.0 - 83.77) > 0.01){
        printf("Error in dummy test 7\n");
    }
}