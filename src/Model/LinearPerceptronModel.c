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
    result->class_labels = get_distinct_class_labels(train_set);
    result->K = result->class_labels->size;
    result->d = instance_continuous_attribute_size(get_instance(train_set, 0));
    result->W = allocate_layer_weights(result->K, result->d + 1, parameter->seed);
    Matrix_ptr bestW = clone(result->W);
    Detailed_classification_performance_ptr best_classification_performance = NULL;
    int epoch = parameter->epoch;
    double learning_rate = parameter->learning_rate;
    for (int i = 0; i < epoch; i++){
        shuffle_instance_list(train_set, parameter->seed);
        for (int j = 0; j < size_of_instance_list(train_set); j++){
            result->x = create_input_vector(get_instance(train_set, j));
            Vector_ptr r_minus_y = calculate_r_minus_y(result, get_instance(train_set, j), result->x, result->W);
            Matrix_ptr delta_W = create_matrix4(r_minus_y, result->x);
            free_vector(r_minus_y);
            multiply_with_constant(delta_W, learning_rate);
            add_matrix(result->W, delta_W);
            free_matrix(delta_W);
            free_vector(result->x);
            free_vector(result->y);
            free_vector(result->r);
        }
        Classifier_ptr validation = validation_linear_perceptron(result);
        Detailed_classification_performance_ptr current_classification_performance = test_classifier(validation, validation_set);
        if (best_classification_performance == NULL || current_classification_performance->accuracy > best_classification_performance->accuracy){
            if (best_classification_performance != NULL){
                free_detailed_classification_performance(best_classification_performance);
            }
            best_classification_performance = current_classification_performance;
            free_matrix(bestW);
            bestW = clone(result->W);
        } else {
            free_detailed_classification_performance(current_classification_performance);
        }
        free(validation);
        learning_rate *= parameter->eta_decrease;
    }
    free_matrix(result->W);
    result->W = bestW;
    return result;
}

/**
 * The allocateLayerWeights method returns a new {@link Matrix} with random weights.
 *
 * @param row    Number of rows.
 * @param column Number of columns.
 * @return Matrix with random weights.
 */
Matrix_ptr allocate_layer_weights(int row, int column, int seed) {
    return create_matrix2(row, column, -0.01, +0.01, seed);
}

/**
 * The createInputVector method takes an {@link Instance} as an input. It converts given Instance to the {@link java.util.Vector}
 * and insert 1.0 to the first element.
 *
 * @param instance Instance to insert 1.0.
 */
Vector_ptr create_input_vector(const Instance *instance) {
    Vector_ptr result = to_vector(instance);
    insert_into_pos(result, 0, 1.0);
    return result;
}

/**
 * The calculateRMinusY method creates a new {@link java.util.Vector} with given Instance, then it multiplies given
 * input Vector with given weights Matrix. After normalizing the output, it return the difference between the newly created
 * Vector and normalized output.
 *
 * @param instance Instance is used to get class labels.
 * @param input    Vector to multiply weights.
 * @param weights  Matrix of weights/
 * @return Difference between newly created Vector and normalized output.
 */
Vector_ptr
calculate_r_minus_y(Linear_perceptron_model_ptr linear_perceptron, const Instance *instance, const Vector *input,
                    const Matrix *weights) {
    int class_index = array_list_index_of(linear_perceptron->class_labels, instance->class_label,
                                          (int (*)(const void *, const void *)) compare_string);
    linear_perceptron->r = create_vector3(linear_perceptron->K, class_index, 1.0);
    Vector_ptr o = multiply_with_vector_from_right(weights, input);
    linear_perceptron->y = normalize_output(o);
    free_vector(o);
    return vector_difference(linear_perceptron->r, linear_perceptron->y);
}

/**
 * The normalizeOutput method takes an input {@link Vector} o, gets the result for e^o of each element of o,
 * then sums them up. At the end, divides the each e^o by the summation.
 *
 * @param o Vector to normalize.
 * @return Normalized vector.
 */
Vector_ptr normalize_output(const Vector *o) {
    double sum = 0.0;
    Array_list_ptr values = create_array_list();
    for (int i = 0; i < o->size; i++){
        sum += exp(get_value(o, i));
    }
    for (int i = 0; i < o->size; i++){
        double* value = malloc(sizeof(double));
        *value = exp(get_value(o, i)) / sum;
        array_list_add(values, value);
    }
    return create_vector(values);
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
    linear_perceptron->x = create_input_vector(instance);
    calculate_output_linear_perceptron(linear_perceptron);
    char* class_label = array_list_get(linear_perceptron->class_labels, max_index_of_vector(linear_perceptron->y));
    free_vector(linear_perceptron->y);
    free_vector(linear_perceptron->x);
    return class_label;
}

Hash_map_ptr predict_probability_linear_perceptron(const void *model, const Instance *instance) {
    Linear_perceptron_model_ptr linear_perceptron = (Linear_perceptron_model_ptr) model;
    linear_perceptron->x = create_input_vector(instance);
    calculate_output_linear_perceptron(linear_perceptron);
    Hash_map_ptr result = create_string_hash_map();
    for (int i = 0; i < linear_perceptron->class_labels->size; i++){
        double *probability = malloc(sizeof(double));
        *probability = get_value(linear_perceptron->y, i);
        hash_map_insert(result, array_list_get(linear_perceptron->class_labels, i), probability);
    }
    free_vector(linear_perceptron->y);
    free_vector(linear_perceptron->x);
    return result;
}

/**
 * The calculateOutput method calculates the {@link Matrix} y by multiplying Matrix W with {@link Vector} x.
 */
void calculate_output_linear_perceptron(Linear_perceptron_model_ptr linear_perceptron) {
    linear_perceptron->y = multiply_with_vector_from_right(linear_perceptron->W, linear_perceptron->x);
}

void free_linear_perceptron_model(Linear_perceptron_model_ptr linear_perceptron) {
    free_matrix(linear_perceptron->W);
    free_array_list(linear_perceptron->class_labels, NULL);
    free(linear_perceptron);
}

Linear_perceptron_model_ptr create_linear_perceptron_model2(const char *file_name) {
    Linear_perceptron_model_ptr result = malloc(sizeof(Linear_perceptron_model));
    FILE* input_file = fopen(file_name, "r");
    fscanf(input_file, "%d%d", &(result->K), &(result->d));
    result->class_labels = create_array_list();
    for (int i = 0; i < result->K; i++){
        char class_label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", class_label);
        array_list_add(result->class_labels, class_label);
    }
    result->W = create_matrix5(input_file);
    fclose(input_file);
    return result;
}
