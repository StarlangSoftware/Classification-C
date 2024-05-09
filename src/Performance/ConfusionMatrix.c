//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#include <CounterHashMap.h>
#include <Memory/Memory.h>
#include "ConfusionMatrix.h"

Confusion_matrix_ptr create_confusion_matrix() {
    Confusion_matrix_ptr result = malloc_(sizeof(Confusion_matrix), "create_confusion_matrix");
    result->matrix = create_string_hash_map();
    result->class_labels = create_array_list();
    return result;
}

/**
 * Constructor that sets the class labels ArrayList and creates new HashMap matrix
 *
 * @param class_labels ArrayList of String.
 */
Confusion_matrix_ptr create_confusion_matrix2(Array_list_ptr class_labels) {
    Confusion_matrix_ptr result = malloc_(sizeof(Confusion_matrix), "create_confusion_matrix2");
    result->matrix = create_string_hash_map();
    result->class_labels = class_labels;
    return result;
}

/**
 * Frees memory allocated for confusion matrix.
 * @param confusion_matrix Confusion matrix
 */
void free_confusion_matrix(Confusion_matrix_ptr confusion_matrix) {
    free_hash_map_of_counter_hash_map(confusion_matrix->matrix);
    free_array_list(confusion_matrix->class_labels, NULL);
    free_(confusion_matrix);
}

/**
 * The classify method takes two Strings; actual class and predicted class as inputs. If the matrix map contains
 * given actual class String as a key, it then assigns the corresponding object of that key to a CounterHashMap, if not
 * it creates a new CounterHashMap. Then, it puts the given predicted class String to the counterHashMap and
 * also put this counterHashMap to the matrix map together with the given actual class String.
 *
 * @param actualClass    String input actual class.
 * @param predictedClass String input predicted class.
 */
void classify(Confusion_matrix_ptr confusion_matrix, char *actual_class, char *predicted_class) {
    Counter_hash_map_ptr counter_hash_map;
    if (hash_map_contains(confusion_matrix->matrix, actual_class)){
        counter_hash_map = hash_map_get(confusion_matrix->matrix, actual_class);
        put_counter_hash_map(counter_hash_map, predicted_class);
    } else {
        counter_hash_map = create_counter_hash_map((unsigned int (*)(const void *, int)) hash_function_string,
                                                   (int (*)(const void *, const void *)) compare_string);
        put_counter_hash_map(counter_hash_map, predicted_class);
        hash_map_insert(confusion_matrix->matrix, actual_class, counter_hash_map);
    }
}

/**
 * The addConfusionMatrix method takes a ConfusionMatrix as an input and loops through actual classes of that HashMap
 * and initially gets one row at a time. Then it puts the current row to the matrix HashMap together with the actual class string.
 *
 * @param confusion_matrix2 ConfusionMatrix input.
 */
void add_confusion_matrix(Confusion_matrix_ptr confusion_matrix, const Confusion_matrix* confusion_matrix2) {
    Array_list_ptr list = key_list(confusion_matrix2->matrix);
    for (int i = 0; i < list->size; i++){
        char* key = array_list_get(list, i);
        Counter_hash_map_ptr rowToBeAdded = hash_map_get(confusion_matrix2->matrix, key);
        if (hash_map_contains(confusion_matrix->matrix, key)){
            Counter_hash_map_ptr currentRow = hash_map_get(confusion_matrix->matrix, key);
            add_counter_hash_map(currentRow, rowToBeAdded);
            hash_map_insert(confusion_matrix->matrix, key, currentRow);
        } else {
            hash_map_insert(confusion_matrix->matrix, key, rowToBeAdded);
        }
    }
    free_array_list(list, NULL);
}

/**
 * The sumOfElements method loops through the keys in matrix HashMap and returns the summation of all the values of the keys.
 * I.e: TP+TN+FP+FN.
 *
 * @return The summation of values.
 */
double sum_of_elements(const Confusion_matrix* confusion_matrix) {
    double result = 0;
    Array_list_ptr list = key_list(confusion_matrix->matrix);
    for (int i = 0; i < list->size; i++){
        char* key = array_list_get(list, i);
        Counter_hash_map_ptr counter_hash_map = hash_map_get(confusion_matrix->matrix, key);
        result += sum_of_counts_counter_hash_map(counter_hash_map);
    }
    free_array_list(list, NULL);
    return result;
}

/**
 * The trace_confusion method loops through the keys in matrix HashMap and if the current key contains the actual key,
 * it accumulates the corresponding values. I.e: TP+TN.
 *
 * @return Summation of values.
 */
double trace_confusion(const Confusion_matrix* confusion_matrix) {
    double result = 0;
    Array_list_ptr list = key_list(confusion_matrix->matrix);
    for (int i = 0; i < list->size; i++){
        char* key = array_list_get(list, i);
        Counter_hash_map_ptr counter_hash_map = hash_map_get(confusion_matrix->matrix, key);
        if (hash_map_contains(counter_hash_map->map, key)){
            result += count_counter_hash_map(counter_hash_map, key);
        }
    }
    free_array_list(list, NULL);
    return result;
}

/**
 * The columnSum method takes a String predicted class as input, and loops through the keys in matrix HashMap.
 * If the current key contains the predicted class String, it accumulates the corresponding values. I.e: TP+FP.
 *
 * @param predictedClass String input predicted class.
 * @return Summation of values.
 */
double column_sum_confusion(const Confusion_matrix* confusion_matrix, const char* predicted_class) {
    double result = 0;
    Array_list_ptr list = key_list(confusion_matrix->matrix);
    for (int i = 0; i < list->size; i++){
        char* key = array_list_get(list, i);
        Counter_hash_map_ptr counter_hash_map = hash_map_get(confusion_matrix->matrix, key);
        if (hash_map_contains(counter_hash_map->map, predicted_class)){
            result += count_counter_hash_map(counter_hash_map, predicted_class);
        }
    }
    free_array_list(list, NULL);
    return result;
}

/**
 * The getAccuracy method returns the result of  TP+TN / TP+TN+FP+FN
 *
 * @return the result of  TP+TN / TP+TN+FP+FN
 */
double get_accuracy(const Confusion_matrix* confusion_matrix) {
    return trace_confusion(confusion_matrix) / sum_of_elements(confusion_matrix);
}

/**
 * The precision method loops through the class labels and returns the resulting Array which has the result of TP/FP+TP.
 *
 * @return The result of TP/FP+TP.
 */
double *precision(const Confusion_matrix* confusion_matrix) {
    double* result = calloc_(confusion_matrix->class_labels->size, sizeof(double), "precision");
    for (int i = 0; i < confusion_matrix->class_labels->size; i++){
        char* actual_class = array_list_get(confusion_matrix->class_labels, i);
        if (hash_map_contains(confusion_matrix->matrix, actual_class)){
            Counter_hash_map_ptr counter_hash_map = hash_map_get(confusion_matrix->matrix, actual_class);
            result[i] = count_counter_hash_map(counter_hash_map, actual_class) /
                    column_sum_confusion(confusion_matrix, actual_class);
        }
    }
    return result;
}

/**
 * The recall method loops through the class labels and returns the resulting Array which has the result of TP/FN+TP.
 *
 * @return The result of TP/FN+TP.
 */
double *recall(const Confusion_matrix* confusion_matrix) {
    double* result = calloc_(confusion_matrix->class_labels->size, sizeof(double), "recall");
    for (int i = 0; i < confusion_matrix->class_labels->size; i++){
        char* actual_class = array_list_get(confusion_matrix->class_labels, i);
        if (hash_map_contains(confusion_matrix->matrix, actual_class)){
            Counter_hash_map_ptr counter_hash_map = hash_map_get(confusion_matrix->matrix, actual_class);
            result[i] = (count_counter_hash_map(counter_hash_map, actual_class) + 0.0) / sum_of_counts_counter_hash_map(counter_hash_map);
        }
    }
    return result;
}

/**
 * The fMeasure method loops through the class labels and returns the resulting Array which has the average of
 * recall and precision.
 *
 * @return The average of recall and precision.
 */
double *f_measure(const Confusion_matrix *confusion_matrix) {
    double* precision_values = precision(confusion_matrix);
    double* recall_values = recall(confusion_matrix);
    double* result = calloc_(confusion_matrix->class_labels->size, sizeof(double), "f_measure");
    for (int i = 0; i < confusion_matrix->class_labels->size; i++){
        result[i] = 2 / (1 / precision_values[i] + 1 / recall_values[i]);
    }
    free_(precision_values);
    free_(recall_values);
    return result;
}

/**
 * The weightedFMeasure method loops through the class labels and returns the resulting Array which has the weighted average of
 * recall and precision.
 *
 * @return The weighted average of recall and precision.
 */
double weighted_f_measure(const Confusion_matrix *confusion_matrix) {
    double* f_measure_values = f_measure(confusion_matrix);
    double sum = 0;
    for (int i = 0; i < confusion_matrix->class_labels->size; i++) {
        char* actual_class = array_list_get(confusion_matrix->class_labels, i);
        Counter_hash_map_ptr counter_hash_map = hash_map_get(confusion_matrix->matrix, actual_class);
        sum += f_measure_values[i] * sum_of_counts_counter_hash_map(counter_hash_map);
    }
    return sum / sum_of_elements(confusion_matrix);

}
