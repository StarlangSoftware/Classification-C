//
// Created by Olcay Taner YILDIZ on 17.07.2023.
//

#include <stdlib.h>
#include <math.h>
#include <FileUtils.h>
#include "LinearPerceptronModel.h"
#include "../Classifier/Classifier.h"
#include "../Classifier/LinearPerceptron.h"

/**
 * Constructor that sets the class labels, their sizes as K and the size of the continuous attributes as d.
 * Constructor also takes {@link InstanceList}s as trainSet and validationSet. Initially it allocates layer weights,
 * then creates an input vector by using given trainSet and finds error. Via the validationSet it finds the classification
 * performance and at the end it reassigns the allocated weight Matrix with the matrix that has the best accuracy.
 *
 * @param trainSet      InstanceList that is used to train.
 * @param validationSet InstanceList that is used to validate.
 * @param parameters    Linear perceptron parameters; learningRate, etaDecrease, crossValidationRatio, epoch.
 */
Linear_perceptron_model_ptr
create_linear_perceptron_model(Instance_list_ptr train_set, Instance_list_ptr validation_set,
                               Linear_perceptron_parameter_ptr parameter) {
    Linear_perceptron_model_ptr result = malloc(sizeof(Linear_perceptron_model));
    result->model = create_neural_network_model(train_set);
    result->W = allocate_layer_weights(result->model->K, result->model->d + 1, parameter->seed);
    Matrix_ptr best_W = clone(result->W);
    Detailed_classification_performance_ptr best_classification_performance = NULL;
    int epoch = parameter->epoch;
    double learning_rate = parameter->learning_rate;
    for (int i = 0; i < epoch; i++){
        shuffle_instance_list(train_set, parameter->seed);
        for (int j = 0; j < size_of_instance_list(train_set); j++){
            result->model->x = create_input_vector(get_instance(train_set, j));
            Vector_ptr r_minus_y = calculate_r_minus_y(result->model, get_instance(train_set, j), result->model->x, result->W);
            Matrix_ptr delta_W = create_matrix4(r_minus_y, result->model->x);
            free_vector(r_minus_y);
            multiply_with_constant(delta_W, learning_rate);
            add_matrix(result->W, delta_W);
            free_matrix(delta_W);
            free_temporary_input_output_vectors(result->model);
        }
        Classifier_ptr validation = validation_linear_perceptron(result);
        Detailed_classification_performance_ptr current_classification_performance = test_classifier(validation, validation_set);
        if (best_classification_performance == NULL || current_classification_performance->accuracy > best_classification_performance->accuracy){
            if (best_classification_performance != NULL){
                free_detailed_classification_performance(best_classification_performance);
            }
            best_classification_performance = current_classification_performance;
            free_matrix(best_W);
            best_W = clone(result->W);
        } else {
            free_detailed_classification_performance(current_classification_performance);
        }
        free(validation);
        learning_rate *= parameter->eta_decrease;
    }
    free_matrix(result->W);
    result->W = best_W;
    return result;
}

/**
 * The predict method takes an {@link Instance} as an input, converts it to a Vector and calculates the {@link Matrix} y by
 * multiplying Matrix W with {@link Vector} x. Then it returns the class label which has the maximum y value.
 *
 * @param instance Instance to predict.
 * @return The class lable which has the maximum y.
 */
char *predict_linear_perceptron(const void *model, const Instance *instance) {
    Linear_perceptron_model_ptr linear_perceptron = (Linear_perceptron_model_ptr) model;
    return predict_neural_network(linear_perceptron->model, instance, model,
                                  (void (*)(const void *)) calculate_output_linear_perceptron);
}

Hash_map_ptr predict_probability_linear_perceptron(const void *model, const Instance *instance) {
    Linear_perceptron_model_ptr linear_perceptron = (Linear_perceptron_model_ptr) model;
    return predict_probability_neural_network(linear_perceptron->model, instance, model,
                                              (void (*)(const void *)) calculate_output_linear_perceptron);
}

/**
 * The calculateOutput method calculates the {@link Matrix} y by multiplying Matrix W with {@link Vector} x.
 */
void calculate_output_linear_perceptron(const Linear_perceptron_model* linear_perceptron) {
    linear_perceptron->model->y = multiply_with_vector_from_right(linear_perceptron->W, linear_perceptron->model->x);
}

void free_linear_perceptron_model(Linear_perceptron_model_ptr linear_perceptron) {
    free_matrix(linear_perceptron->W);
    free_neural_network_model(linear_perceptron->model);
    free(linear_perceptron);
}

Linear_perceptron_model_ptr create_linear_perceptron_model2(const char *file_name) {
    Linear_perceptron_model_ptr result = malloc(sizeof(Linear_perceptron_model));
    FILE* input_file = fopen(file_name, "r");
    result->model = create_neural_network_model2(input_file);
    result->W = create_matrix5(input_file);
    fclose(input_file);
    return result;
}
