//
// Created by Olcay Taner YILDIZ on 21.07.2023.
//

#include <Memory/Memory.h>
#include "DeepNetworkModel.h"
#include "../../InstanceList/Partition.h"

/**
 * The allocateWeights method takes DeepNetworkParameters as an input. First it adds random weights to the ArrayList
 * of Matrix weights' first layer. Then it loops through the layers and adds random weights till the last layer.
 * At the end it adds random weights to the last layer and also sets the hiddenLayerSize value.
 *
 * @param deep_network Current deep network model.
 * @param deep_network_parameter DeepNetworkParameter input.
 */
void allocate_deep_network_weights(Deep_network_model_ptr deep_network, Deep_network_parameter_ptr deep_network_parameter) {
    array_list_add(deep_network->weights, allocate_layer_weights(get_hidden_nodes(deep_network_parameter, 0), deep_network->model->d + 1, deep_network_parameter->seed));
    for (int i = 0; i < layer_size(deep_network_parameter) - 1; i++){
        array_list_add(deep_network->weights, allocate_layer_weights(get_hidden_nodes(deep_network_parameter, i + 1), get_hidden_nodes(deep_network_parameter, i) + 1, deep_network_parameter->seed));
    }
    array_list_add(deep_network->weights, allocate_layer_weights(deep_network->model->K, get_hidden_nodes(deep_network_parameter, layer_size(deep_network_parameter) - 1) + 1, deep_network_parameter->seed));
    deep_network->hidden_layer_size = layer_size(deep_network_parameter);
}

/**
 * Constructor that takes two {@link InstanceList} train set and validation set and {@link DeepNetworkParameter} as inputs.
 * First it sets the class labels, their sizes as K and the size of the continuous attributes as d of given train set and
 * allocates weights and sets the best weights. At each epoch, it shuffles the train set and loops through the each item of that train set,
 * it multiplies the weights Matrix with input Vector than applies the sigmoid function and stores the result as hidden and add bias.
 * Then updates weights and at the end it compares the performance of these weights with validation set. It updates the bestClassificationPerformance and
 * bestWeights according to the current situation. At the end it updates the learning rate via etaDecrease value and finishes
 * with clearing the weights.
 *
 * @param train_set      InstanceList to be used as trainSet.
 * @param validation_set InstanceList to be used as validationSet.
 * @param parameter    DeepNetworkParameter input.
 */
Deep_network_model_ptr create_deep_network_model(Instance_list_ptr train_set, Instance_list_ptr validation_set,
                                                 Deep_network_parameter_ptr parameter) {
    Vector_ptr tmp_hidden = NULL;
    Deep_network_model_ptr result = malloc_(sizeof(Deep_network_model), "create_deep_network_model");
    result->model = create_neural_network_model(train_set);
    result->activation_function = parameter->activation_function;
    result->weights = create_array_list();
    allocate_deep_network_weights(result, parameter);
    Array_list_ptr best_weights = set_best_weights(result);
    Detailed_classification_performance_ptr best_classification_performance = NULL;
    int epoch = parameter->epoch;
    double learning_rate = parameter->learning_rate;
    Array_list_ptr hidden = create_array_list();
    Array_list_ptr hidden_biased = create_array_list();
    Array_list_ptr delta_weights = create_array_list();
    for (int i = 0; i < epoch; i++) {
        shuffle_instance_list(train_set, parameter->seed);
        for (int j = 0; j < size_of_instance_list(train_set); j++) {
            result->model->x = create_input_vector(get_instance(train_set, j));
            array_list_clear(hidden, (void (*)(void *)) free_vector);
            array_list_clear(hidden_biased, (void (*)(void *)) free_vector);
            array_list_clear(delta_weights, (void (*)(void *)) free_matrix);
            for (int k = 0; k < result->hidden_layer_size; k++){
                if (k == 0){
                    array_list_add(hidden, calculate_hidden(result->model->x, array_list_get(result->weights, k), result->activation_function));
                } else {
                    array_list_add(hidden, calculate_hidden(array_list_get(hidden_biased, k - 1), array_list_get(result->weights, k), result->activation_function));
                }
                array_list_add(hidden_biased, biased(array_list_get(hidden, k)));
            }
            Vector_ptr r_minus_y = calculate_r_minus_y(result->model, get_instance(train_set, j), array_list_get(hidden_biased, result->hidden_layer_size - 1),
                                                       array_list_get(result->weights, result->weights->size - 1));
            array_list_insert(delta_weights, 0, create_matrix4(r_minus_y, array_list_get(hidden_biased, result->hidden_layer_size - 1)));
            for (int k = result->weights->size - 2; k >= 0; k--){
                Vector_ptr tmph, one_minus_hidden = NULL, activation_derivative = NULL, one;
                if (k == result->weights->size - 2){
                    tmph = multiply_with_vector_from_left(array_list_get(result->weights, k + 1), r_minus_y);
                    free_vector(r_minus_y);
                } else {
                    tmph = multiply_with_vector_from_left(array_list_get(result->weights, k + 1), tmp_hidden);
                }
                remove_at_pos(tmph, 0);
                switch (result->activation_function) {
                    case SIGMOID:
                        one_minus_hidden = calculate_one_minus_hidden(array_list_get(hidden, k));
                        activation_derivative = element_product_with_vector(one_minus_hidden, array_list_get(hidden, k));
                        free_vector(one_minus_hidden);
                        break;
                    case TANH:
                        one = create_vector2(hidden->size, 1.0);
                        tanh_of_vector(array_list_get(hidden, k));
                        Vector_ptr tmp_product = element_product_with_vector(array_list_get(hidden, k), array_list_get(hidden, k));
                        activation_derivative = vector_difference(one, tmp_product);
                        free_vector(tmp_product);
                        free_vector(one);
                        break;
                    case RELU:
                        relu_derivative_of_vector(array_list_get(hidden, k));
                        activation_derivative = array_list_get(hidden, k);
                        break;
                }
                if (k != result->weights->size - 2){
                    free_vector(tmp_hidden);
                }
                tmp_hidden = element_product_with_vector(tmph, activation_derivative);
                if (result->activation_function != RELU){
                    free_vector(activation_derivative);
                }
                free_vector(tmph);
                if (k == 0){
                    array_list_insert(delta_weights, 0, create_matrix4(tmp_hidden, result->model->x));
                } else {
                    array_list_insert(delta_weights, 0, create_matrix4(tmp_hidden, array_list_get(hidden_biased, k - 1)));
                }
            }
            free_vector(tmp_hidden);
            for (int k = 0; k < result->weights->size; k++){
                multiply_with_constant(array_list_get(delta_weights, k), learning_rate);
                add_matrix(array_list_get(result->weights, k), array_list_get(delta_weights, k));
            }
            free_temporary_input_output_vectors(result->model);
        }
        Model_ptr validation = validation_deep_network(result);
        Detailed_classification_performance_ptr current_classification_performance = test_classifier(validation, validation_set);
        if (best_classification_performance == NULL || current_classification_performance->accuracy > best_classification_performance->accuracy){
            if (best_classification_performance != NULL){
                free_detailed_classification_performance(best_classification_performance);
            }
            best_classification_performance = current_classification_performance;
            free_array_list(best_weights, (void (*)(void *)) free_matrix);
            best_weights = set_best_weights(result);
        } else {
            free_detailed_classification_performance(current_classification_performance);
        }
        free_(validation);
        learning_rate *= parameter->eta_decrease;
    }
    free_array_list(hidden, (void (*)(void *)) free_vector);
    free_array_list(hidden_biased, (void (*)(void *)) free_vector);
    free_array_list(delta_weights, (void (*)(void *)) free_matrix);
    array_list_clear(result->weights, (void (*)(void *)) free_matrix);
    for (int i = 0; i < best_weights->size; i++){
        array_list_add(result->weights, array_list_get(best_weights, i));
    }
    free_array_list(best_weights, NULL);
    free_detailed_classification_performance(best_classification_performance);
    return result;
}

/**
 * The setBestWeights method creates an vector of Matrix as bestWeights and clones the values of weights ArrayList
 * into this newly created vector.
 *
 * @return An vector clones from the weights ArrayList.
 */
Array_list_ptr set_best_weights(Deep_network_model_ptr deep_network) {
    Array_list_ptr best_weights = create_array_list();
    for (int i = 0; i < deep_network->weights->size; i++){
        array_list_add(best_weights, clone((Matrix_ptr) array_list_get(deep_network->weights, i)));
    }
    return best_weights;
}

/**
 * Frees memory allocated for deep network
 * @param deep_network Deep network
 */
void free_deep_network_model(Deep_network_model_ptr deep_network) {
    free_neural_network_model(deep_network->model);
    free_array_list(deep_network->weights, (void (*)(void *)) free_matrix);
    free_(deep_network);
}

/**
 * Loads a deep network model from an input model file.
 * @param file_name Model file name.
 */
Deep_network_model_ptr create_deep_network_model2(const char *file_name) {
    Deep_network_model_ptr result = malloc_(sizeof(Deep_network_model), "create_deep_network_model2");
    FILE* input_file = fopen(file_name, "r");
    result->model = create_neural_network_model2(input_file);
    fscanf(input_file, "%d", &(result->hidden_layer_size));
    result->weights = create_array_list();
    for (int i = 0; i < result->hidden_layer_size + 1; i++){
        array_list_add(result->weights, create_matrix5(input_file));
    }
    result->activation_function = get_activation_function(input_file);
    return result;
}

char *predict_deep_network(const void *model, const Instance *instance) {
    Deep_network_model_ptr deep_network = (Deep_network_model_ptr) model;
    return predict_neural_network(deep_network->model, instance, model,
                                  (void (*)(const void *)) calculate_output_deep_network);
}

/**
 * Calculates the posterior probability distribution for the given instance according to deep network model.
 * @param model Current deep network model
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr predict_probability_deep_network(const void *model, const Instance *instance) {
    Deep_network_model_ptr deep_network = (Deep_network_model_ptr) model;
    return predict_probability_neural_network(deep_network->model, instance, model,
                                              (void (*)(const void *)) calculate_output_deep_network);
}

void calculate_output_deep_network(const Deep_network_model *deep_network) {
    Vector_ptr hidden = NULL, hidden_biased = NULL;
    for (int i = 0; i < deep_network->weights->size - 1; i++){
        if (i == 0){
            hidden = calculate_hidden(deep_network->model->x, array_list_get(deep_network->weights, i), deep_network->activation_function);
        } else {
            free_vector(hidden);
            hidden = calculate_hidden(hidden_biased, array_list_get(deep_network->weights, i), deep_network->activation_function);
        }
        if (i != 0){
            free_vector(hidden_biased);
        }
        hidden_biased = biased(hidden);
    }
    deep_network->model->y = multiply_with_vector_from_right(array_list_get(deep_network->weights, deep_network->weights->size - 1), hidden_biased);
    free_vector(hidden);
    free_vector(hidden_biased);
}

/**
 * Training algorithm for deep network classifier.
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter Parameters of the deep network algorithm. crossValidationRatio and seed are used as parameters.
 * @throws DiscreteFeaturesNotAllowed Exception for discrete features.
 */
Model_ptr train_deep_network(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_deep_network");
    Deep_network_parameter_ptr deep_network_parameter = (Deep_network_parameter_ptr) parameter;
    Partition_ptr partition = create_partition4(train_set, deep_network_parameter->cross_validation_ratio, deep_network_parameter->seed, true);
    result->model = create_deep_network_model(get_instance_list(partition, 1), get_instance_list(partition, 0), deep_network_parameter);
    result->train = train_deep_network;
    result->predict_probability = predict_probability_deep_network;
    result->predict = predict_deep_network;
    free_partition(partition);
    return result;
}

/**
 * Loads the deep network model from an input file.
 * @param file_name File name of the deep network model.
 */
Model_ptr load_deep_network(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_deep_network");
    result->model = create_deep_network_model2(file_name);
    result->train = train_deep_network;
    result->predict_probability = predict_probability_deep_network;
    result->predict = predict_deep_network;
    return result;
}

Model_ptr validation_deep_network(Deep_network_model_ptr deep_network) {
    Model_ptr result = malloc_(sizeof(Model), "validation_deep_network");
    result->model = deep_network;
    result->train = train_deep_network;
    result->predict_probability = predict_probability_deep_network;
    result->predict = predict_deep_network;
    return result;
}

/**
 * Frees memory allocated for deep network model
 * @param deep_network Deep network model
 */
void free_deep_network(Model_ptr deep_network) {
    free_deep_network_model(deep_network->model);
    free_(deep_network);
}
