//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#include <stdlib.h>
#include "Dummy.h"
#include "../Model/DummyModel.h"

Classifier_ptr train_dummy(Instance_list_ptr train_set, void *parameter) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_dummy_model(train_set);
    return result;
}

Classifier_ptr load_dummy(char *file_name) {
    Classifier_ptr result = malloc(sizeof(Classifier));
    result->model = create_dummy_model2(file_name);
    return result;
}

Detailed_classification_performance_ptr test_dummy(Classifier_ptr dummy, Instance_list_ptr test_set) {
    Array_list_ptr class_labels = get_distinct_class_labels(test_set);
    Confusion_matrix_ptr confusion = create_confusion_matrix2(class_labels);
    for (int i = 0; i < size_of_instance_list(test_set); i++){
        Instance_ptr instance = get_instance(test_set, i);
        classify(confusion, instance->class_label, predict_dummy(dummy->model, instance));
    }
    return create_detailed_classification_performance(confusion);
}

void free_dummy(Classifier_ptr dummy) {
    free_discrete_distribution(dummy->model);
    free(dummy);
}
