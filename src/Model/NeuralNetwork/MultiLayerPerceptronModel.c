//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#include <Memory/Memory.h>
#include "MultiLayerPerceptronModel.h"
#include "../../InstanceList/Partition.h"

/**
 * A constructor that takes {@link InstanceList}s as trainsSet and validationSet. It  sets the {@link NeuralNetworkModel}
 * nodes with given {@link InstanceList} then creates an input vector by using given trainSet and finds error.
 * Via the validationSet it finds the classification performance and reassigns the allocated weight Matrix with the matrix
 * that has the best accuracy and the Matrix V with the best Vector input.
 *
 * @param train_set      InstanceList that is used to train.
 * @param validation_set InstanceList that is used to validate.
 * @param parameter    Multi layer perceptron parameters; seed, learningRate, etaDecrease, crossValidationRatio, epoch, hiddenNodes.
 */
Multi_layer_perceptron_model_ptr
create_multi_layer_perceptron_model(Instance_list_ptr train_set, Instance_list_ptr validation_set,
                                    Multi_layer_perceptron_parameter_ptr parameter) {
    Multi_layer_perceptron_model_ptr result = malloc_(sizeof(Multi_layer_perceptron_model), "create_multi_layer_perceptron_model");
    result->model = create_neural_network_model(train_set);
    Matrix_ptr best_W = NULL, best_V = NULL;
    Vector_ptr activation_derivative = NULL, one_minus_hidden = NULL, one = NULL;
    result->activation_function = parameter->activation_function;
    allocate_weights(result, parameter->hidden_nodes, parameter->seed);
    best_W = clone(result->W);
    best_V = clone(result->V);
    Detailed_classification_performance_ptr best_classification_performance = NULL;
    int epoch = parameter->epoch;
    double learning_rate = parameter->learning_rate;
    for (int i = 0; i < epoch; i++) {
        shuffle_instance_list(train_set, parameter->seed);
        for (int j = 0; j < size_of_instance_list(train_set); j++) {
            result->model->x = create_input_vector(get_instance(train_set, j));
            Vector_ptr hidden = calculate_hidden(result->model->x, result->W, result->activation_function);
            Vector_ptr hidden_biased = biased(hidden);
            Vector_ptr r_minus_y = calculate_r_minus_y(result->model, get_instance(train_set, j), hidden_biased, result->V);
            Matrix_ptr delta_V = create_matrix4(r_minus_y, hidden_biased);
            free_vector(hidden_biased);
            Vector_ptr tmph = multiply_with_vector_from_left(result->V, r_minus_y);
            free_vector(r_minus_y);
            remove_at_pos(tmph, 0);
            switch (result->activation_function) {
                case SIGMOID:
                    one_minus_hidden = calculate_one_minus_hidden(hidden);
                    activation_derivative = element_product_with_vector(one_minus_hidden, hidden);
                    free_vector(one_minus_hidden);
                    break;
                case TANH:
                    one = create_vector2(hidden->size, 1.0);
                    tanh_of_vector(hidden);
                    Vector_ptr tmp_product = element_product_with_vector(hidden, hidden);
                    activation_derivative = vector_difference(one, tmp_product);
                    free_vector(tmp_product);
                    free_vector(one);
                    break;
                case RELU:
                    relu_derivative_of_vector(hidden);
                    activation_derivative = hidden;
                    break;
            }
            free_vector(hidden);
            Vector_ptr tmp_hidden = element_product_with_vector(tmph, activation_derivative);
            if (result->activation_function != RELU){
                free_vector(activation_derivative);
            }
            free_vector(tmph);
            Matrix_ptr delta_W = create_matrix4(tmp_hidden, result->model->x);
            free_vector(tmp_hidden);
            multiply_with_constant(delta_V, learning_rate);
            add_matrix(result->V, delta_V);
            free_matrix(delta_V);
            multiply_with_constant(delta_W, learning_rate);
            add_matrix(result->W, delta_W);
            free_matrix(delta_W);
            free_temporary_input_output_vectors(result->model);
        }
        Model_ptr validation = validation_multi_layer_perceptron(result);
        Detailed_classification_performance_ptr current_classification_performance = test_classifier(validation, validation_set);
        if (best_classification_performance == NULL || current_classification_performance->accuracy > best_classification_performance->accuracy){
            if (best_classification_performance != NULL){
                free_detailed_classification_performance(best_classification_performance);
            }
            best_classification_performance = current_classification_performance;
            free_matrix(best_W);
            best_W = clone(result->W);
            free_matrix(best_V);
            best_V = clone(result->V);
        } else {
            free_detailed_classification_performance(current_classification_performance);
        }
        free_(validation);
        learning_rate *= parameter->eta_decrease;
    }
    free_detailed_classification_performance(best_classification_performance);
    free_matrix(result->W);
    result->W = best_W;
    free_matrix(result->V);
    result->V = best_V;
    return result;
}

/**
 * The allocateWeights method allocates layers' weights of Matrix W and V.
 *
 * @param multi_layer_perceptron Multilayer perceptron model
 * @param H Integer value for weights.
 * @param seed Seed to set the randomizer.
 */
void allocate_weights(Multi_layer_perceptron_model_ptr multi_layer_perceptron, int H, int seed) {
    multi_layer_perceptron->W = allocate_layer_weights(H, multi_layer_perceptron->model->d + 1, seed);
    multi_layer_perceptron->V = allocate_layer_weights(multi_layer_perceptron->model->K, H + 1, seed);
}

/**
 * Frees memory allocated for multi layer perceptron model
 * @param multi_layer_perceptron Multi layer perceptron model
 */
void free_multi_layer_perceptron_model(Multi_layer_perceptron_model_ptr multi_layer_perceptron) {
    free_neural_network_model(multi_layer_perceptron->model);
    free_matrix(multi_layer_perceptron->V);
    free_matrix(multi_layer_perceptron->W);
    free_(multi_layer_perceptron);
}

/**
 * The calculateOutput method calculates the forward single hidden layer by using Matrices W and V.
 * @param multi_layer_perceptron Multilayer perceptron model
 */
void calculate_output_multi_layer_perceptron(const Multi_layer_perceptron_model* multi_layer_perceptron) {
    calculate_forward_single_hidden_layer(multi_layer_perceptron->model, multi_layer_perceptron->W, multi_layer_perceptron->V, multi_layer_perceptron->activation_function);
}

char *predict_multi_layer_perceptron(const void *model, const Instance *instance) {
    Multi_layer_perceptron_model_ptr multi_layer_perceptron = (Multi_layer_perceptron_model_ptr) model;
    return predict_neural_network(multi_layer_perceptron->model, instance, model,
                                  (void (*)(const void *)) calculate_output_multi_layer_perceptron);
}

/**
 * Calculates the posterior probability distribution for the given instance according to multi layer neural network model.
 * @param model Multilayer perceptron model
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr predict_probability_multi_layer_perceptron(const void *model, const Instance *instance) {
    Multi_layer_perceptron_model_ptr multi_layer_perceptron = (Multi_layer_perceptron_model_ptr) model;
    return predict_probability_neural_network(multi_layer_perceptron->model, instance, model,
                                              (void (*)(const void *)) calculate_output_multi_layer_perceptron);
}

/**
 * Loads a multi-layer perceptron model from an input model file.
 * @param file_name Model file name.
 */
Multi_layer_perceptron_model_ptr create_multi_layer_perceptron_model2(const char *file_name) {
    Multi_layer_perceptron_model_ptr result = malloc_(sizeof(Multi_layer_perceptron_model), "create_multi_layer_perceptron_model2");
    FILE* input_file = fopen(file_name, "r");
    result->model = create_neural_network_model2(input_file);
    result->W = create_matrix5(input_file);
    result->V = create_matrix5(input_file);
    result->activation_function = get_activation_function(input_file);
    fclose(input_file);
    return result;
}

/**
 * Training algorithm for the multilayer perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the multilayer perceptron with
 * gradient descent.
 *
 * @param train_set   Training data given to the algorithm
 * @param parameter Parameters of the multilayer perceptron.
 */
Model_ptr train_multi_layer_perceptron(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model), "train_multi_layer_perceptron");
    Multi_layer_perceptron_parameter_ptr multi_layer_perceptron_parameter = (Multi_layer_perceptron_parameter_ptr) parameter;
    Partition_ptr partition = create_partition4(train_set, multi_layer_perceptron_parameter->cross_validation_ratio, multi_layer_perceptron_parameter->seed, true);
    result->model = create_multi_layer_perceptron_model(get_instance_list(partition, 1), get_instance_list(partition, 0), multi_layer_perceptron_parameter);
    result->train = train_multi_layer_perceptron;
    result->predict_probability = predict_probability_multi_layer_perceptron;
    result->predict = predict_multi_layer_perceptron;
    free_partition(partition);
    return result;
}

/**
 * Loads the multi-layer perceptron model from an input file.
 * @param file_name File name of the multi-layer perceptron model.
 */
Model_ptr load_multi_layer_perceptron(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model), "load_multi_layer_perceptron");
    result->model = create_multi_layer_perceptron_model2(file_name);
    result->train = train_multi_layer_perceptron;
    result->predict_probability = predict_probability_multi_layer_perceptron;
    result->predict = predict_multi_layer_perceptron;
    return result;

}

Model_ptr validation_multi_layer_perceptron(Multi_layer_perceptron_model_ptr multi_layer_perceptron) {
    Model_ptr result = malloc_(sizeof(Model), "validation_multi_layer_perceptron");
    result->model = multi_layer_perceptron;
    result->train = train_multi_layer_perceptron;
    result->predict_probability = predict_probability_multi_layer_perceptron;
    result->predict = predict_multi_layer_perceptron;
    return result;
}

/**
 * Frees memory allocated for multilayer perceptron model
 * @param multi_layer_perceptron Multilayer perceptron model
 */
void free_multi_layer_perceptron(Model_ptr multi_layer_perceptron) {
    free_multi_layer_perceptron_model(multi_layer_perceptron->model);
    free_(multi_layer_perceptron);
}
