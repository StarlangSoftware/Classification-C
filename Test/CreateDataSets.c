//
// Created by Olcay Taner YILDIZ on 22.06.2023.
//

#include <stdlib.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"

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