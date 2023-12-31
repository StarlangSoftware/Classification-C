//
// Created by Olcay Taner YILDIZ on 18.06.2023.
//

#include <stdio.h>
#include <Memory/Memory.h>
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
    String_ptr s = get_classes(iris);
    if (!string_equals2(s, "Iris-setosa;Iris-versicolor;Iris-virginica")){
        printf("Error in get classes 1");
    }
    free_string_ptr(s);
    s = get_classes(bupa);
    if (!string_equals2(s, "1;2")){
        printf("Error in get classes 2");
    }
    free_string_ptr(s);
    s = get_classes(dermatology);
    if (!string_equals2(s, "2;1;3;5;4;6")){
        printf("Error in get classes 3");
    }
    free_string_ptr(s);
    s = get_classes(car);
    if (!string_equals2(s, "unacc;acc;vgood;good")){
        printf("Error in get classes 4");
    }
    free_string_ptr(s);
    s = get_classes(tictactoe);
    if (!string_equals2(s, "positive;negative")){
        printf("Error in get classes 5");
    }
    free_string_ptr(s);
    s = get_classes(nursery);
    if (!string_equals2(s, "recommend;priority;not_recom;very_recom;spec_prior")){
        printf("Error in get classes 6");
    }
    free_string_ptr(s);
    s = get_classes(chess);
    if (!string_equals2(s, "draw;zero;one;two;three;four;five;six;seven;eight;nine;ten;eleven;twelve;thirteen;fourteen;fifteen;sixteen")){
        printf("Error in get classes 7");
    }
    free_string_ptr(s);
}

int main(){
    create_datasets();
    test_sample_size();
    test_class_count();
    test_get_classes();
    free_datasets();
}