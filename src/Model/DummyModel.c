//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#include <Memory/Memory.h>
#include "DummyModel.h"

/**
 * Constructor which sets the distribution using the given InstanceList.
 *
 * @param train_set InstanceList which is used to get the class distribution.
 */
Dummy_model_ptr create_dummy_model(Instance_list_ptr train_set) {
    Dummy_model_ptr result = malloc_(sizeof(Dummy_model), "create_dummy_model");
    result->distribution = class_distribution(train_set);
    return result;
}

/**
 * Frees memory allocated for dummy model.
 * @param dummy_model Dummy model
 */
void free_dummy_model(Dummy_model_ptr dummy_model) {
    free_discrete_distribution(dummy_model->distribution);
    free_(dummy_model);
}

/**
 * Loads a dummy model from an input model file.
 * @param file_name Model file name.
 */
Dummy_model_ptr create_dummy_model2(const char *file_name) {
    Dummy_model_ptr result = malloc_(sizeof(Dummy_model), "create_dummy_model2");
    FILE* input_file = fopen(file_name, "r");
    result->distribution = create_discrete_distribution2(input_file);
    fclose(input_file);
    return result;
}

/**
 * The predict method takes an Instance as an input and returns the entry of distribution which has the maximum value.
 *
 * @param model Current model
 * @param instance Instance to make prediction.
 * @return The entry of distribution which has the maximum value.
 */
char *predict_dummy(const void* model, const Instance* instance) {
    return get_max_item(((Dummy_model_ptr) model)->distribution);
}

/**
 * Calculates the posterior probability distribution for the given instance according to dummy model.
 * @param model Current model
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr predict_probability_dummy(const void* model, const Instance* instance) {
    return get_probability_distribution(((Dummy_model_ptr) model)->distribution);
}

/**
 * Training algorithm for the dummy classifier. Actually dummy classifier returns the maximum occurring class in
 * the training data, there is no training.
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter -
 */
Model_ptr train_dummy(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_dummy");
    result->model = create_dummy_model(train_set);
    result->train = train_dummy;
    result->predict = predict_dummy;
    result->predict_probability = predict_probability_dummy;
    return result;
}

/**
 * Loads the dummy model from an input file.
 * @param file_name File name of the dummy model.
 */
Model_ptr load_dummy(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_dummy");
    result->model = create_dummy_model2(file_name);
    result->train = train_dummy;
    result->predict = predict_dummy;
    result->predict_probability = predict_probability_dummy;
    return result;
}

/**
 * Frees memory allocated for the dummy model
 * @param dummy Dummy model
 */
void free_dummy(Model_ptr dummy) {
    free_dummy_model(dummy->model);
    free_(dummy);
}
