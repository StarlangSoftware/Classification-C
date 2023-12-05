//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#include <Memory/Memory.h>
#include "Dummy.h"
#include "../Model/DummyModel.h"

Classifier_ptr train_dummy(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_dummy");
    result->model = create_dummy_model(train_set);
    result->train = train_dummy;
    result->predict = predict_dummy;
    result->predict_probability = predict_probability_dummy;
    return result;
}

Classifier_ptr load_dummy(const char *file_name) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "load_dummy");
    result->model = create_dummy_model2(file_name);
    result->train = train_dummy;
    result->predict = predict_dummy;
    result->predict_probability = predict_probability_dummy;
    return result;
}

void free_dummy(Classifier_ptr dummy) {
    free_dummy_model(dummy->model);
    free_(dummy);
}
