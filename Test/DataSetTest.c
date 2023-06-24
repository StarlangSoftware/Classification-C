//
// Created by Olcay Taner YILDIZ on 18.06.2023.
//

#include <stdio.h>
#include "../src/DataSet/DataSet.h"
#include "CreateDataSets.h"

void test_sample_size(){
    if (sample_size(iris) != 150){
        printf("Error in sample size 1");
    }
    if (sample_size(bupa) != 345){
        printf("Error in sample size 2");
    }
    if (sample_size(dermatology) != 366){
        printf("Error in sample size 3");
    }
    if (sample_size(car) != 1728){
        printf("Error in sample size 4");
    }
    if (sample_size(tictactoe) != 958){
        printf("Error in sample size 5");
    }
    if (sample_size(nursery) != 12960){
        printf("Error in sample size 6");
    }
    if (sample_size(chess) != 28056){
        printf("Error in sample size 7");
    }
}

void test_class_count(){
    if (class_count(iris) != 3){
        printf("Error in class size 1");
    }
    if (class_count(bupa) != 2){
        printf("Error in class size 2");
    }
    if (class_count(dermatology) != 6){
        printf("Error in class size 3");
    }
    if (class_count(car) != 4){
        printf("Error in class size 4");
    }
    if (class_count(tictactoe) != 2){
        printf("Error in class size 5");
    }
    if (class_count(nursery) != 5){
        printf("Error in class size 6");
    }
    if (class_count(chess) != 18){
        printf("Error in class size 7");
    }
}

void test_get_classes(){
    if (!string_equals2(get_classes(iris), "Iris-setosa;Iris-versicolor;Iris-virginica")){
        printf("Error in get classes 1");
    }
    if (!string_equals2(get_classes(bupa), "1;2")){
        printf("Error in get classes 2");
    }
    if (!string_equals2(get_classes(dermatology), "2;1;3;5;4;6")){
        printf("Error in get classes 3");
    }
    if (!string_equals2(get_classes(car), "unacc;acc;vgood;good")){
        printf("Error in get classes 4");
    }
    if (!string_equals2(get_classes(tictactoe), "positive;negative")){
        printf("Error in get classes 5");
    }
    if (!string_equals2(get_classes(nursery), "recommend;priority;not_recom;very_recom;spec_prior")){
        printf("Error in get classes 6");
    }
    if (!string_equals2(get_classes(chess), "draw;zero;one;two;three;four;five;six;seven;eight;nine;ten;eleven;twelve;thirteen;fourteen;fifteen;sixteen")){
        printf("Error in get classes 7");
    }
}

int main(){
    create_datasets();
    test_sample_size();
    test_class_count();
    test_get_classes();
    free_data_set(iris);
    free_data_set(bupa);
    free_data_set(dermatology);
    free_data_set(car);
    free_data_set(tictactoe);
    free_data_set(nursery);
    free_data_set(chess);
}