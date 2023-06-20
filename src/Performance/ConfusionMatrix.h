//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#ifndef CLASSIFICATION_CONFUSIONMATRIX_H
#define CLASSIFICATION_CONFUSIONMATRIX_H

#include <HashMap/HashMap.h>

struct confusion_matrix {
    Hash_map_ptr matrix;
    Array_list_ptr class_labels;
};

typedef struct confusion_matrix Confusion_matrix;

typedef Confusion_matrix *Confusion_matrix_ptr;

Confusion_matrix_ptr create_confusion_matrix();

Confusion_matrix_ptr create_confusion_matrix2(Array_list_ptr class_labels);

void classify(Confusion_matrix_ptr confusion_matrix, char *actual_class, char *predicted_class);

void free_confusion_matrix(Confusion_matrix_ptr confusion_matrix);

void add_confusion_matrix(Confusion_matrix_ptr confusion_matrix, const Confusion_matrix *confusion_matrix2);

double sum_of_elements(const Confusion_matrix *confusion_matrix);

double trace_confusion(const Confusion_matrix *confusion_matrix);

double column_sum_confusion(const Confusion_matrix *confusion_matrix, const char *predicted_class);

double get_accuracy(const Confusion_matrix *confusion_matrix);

double *precision(const Confusion_matrix *confusion_matrix);

double *recall(const Confusion_matrix *confusion_matrix);

double *f_measure(const Confusion_matrix *confusion_matrix);

double weighted_f_measure(const Confusion_matrix *confusion_matrix);

#endif //CLASSIFICATION_CONFUSIONMATRIX_H
