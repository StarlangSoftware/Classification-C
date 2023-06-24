//
// Created by Olcay Taner YILDIZ on 22.06.2023.
//
#include "Classifier.h"
#include "CounterHashMap.h"

Detailed_classification_performance_ptr test_classifier(const Classifier* classifier, const Instance_list* test_set) {
    Array_list_ptr class_labels = get_distinct_class_labels(test_set);
    Confusion_matrix_ptr confusion = create_confusion_matrix2(class_labels);
    for (int i = 0; i < size_of_instance_list(test_set); i++){
        Instance_ptr instance = get_instance(test_set, i);
        classify(confusion, instance->class_label, classifier->predict(classifier->model, instance));
    }
    return create_detailed_classification_performance(confusion);
}

char *get_maximum(Array_list_ptr class_labels) {
    Counter_hash_map_ptr frequencies = create_counter_hash_map(
            (unsigned int (*)(const void *, int)) hash_function_string,
            (int (*)(const void *, const void *)) compare_string);
    for (int i = 0; i < class_labels->size; i++){
        put_counter_hash_map(frequencies, array_list_get(class_labels, i));
    }
    char* result = max_counter_hash_map(frequencies);
    free_counter_hash_map(frequencies, NULL);
    return result;
}

