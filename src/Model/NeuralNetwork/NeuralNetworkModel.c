//
// Created by Olcay Taner YILDIZ on 19.07.2023.
//

#include <stdlib.h>
#include <math.h>
#include <FileUtils.h>
#include <string.h>
#include <Memory/Memory.h>
#include "NeuralNetworkModel.h"

/**
 * Constructor that sets the class labels, their sizes as K and the size of the continuous attributes as d.
 *
 * @param trainSet InstanceList to use as train set.
 */
Neural_network_model_ptr create_neural_network_model(const Instance_list *train_set) {
    Neural_network_model_ptr result = malloc_(sizeof(Neural_network_model), "create_neural_network_model");
    result->class_labels = get_distinct_class_labels(train_set);
    result->K = result->class_labels->size;
    result->d = instance_continuous_attribute_size(get_instance(train_set, 0));
    return result;
}

/**
 * Frees memory allocated for neural network vectors.
 * @param neural_network Neural network
 */
void free_temporary_input_output_vectors(Neural_network_model_ptr neural_network) {
    free_vector(neural_network->x);
    free_vector(neural_network->y);
    free_vector(neural_network->r);
}

/**
 * The normalizeOutput method takes an input Vector o, gets the result for e^o of each element of o,
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
        array_list_add_double(values, exp(get_value(o, i)) / sum);
    }
    return create_vector(values);
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
calculate_r_minus_y(Neural_network_model_ptr neural_network, const Instance *instance, const Vector *input,
                    const Matrix *weights) {
    int class_index = array_list_index_of(neural_network->class_labels, instance->class_label,
                                          (int (*)(const void *, const void *)) compare_string);
    neural_network->r = create_vector3(neural_network->K, class_index, 1.0);
    Vector_ptr o = multiply_with_vector_from_right(weights, input);
    neural_network->y = normalize_output(o);
    free_vector(o);
    return vector_difference(neural_network->r, neural_network->y);
}

/**
 * The createInputVector method takes an Instance as an input. It converts given Instance to the {@link java.util.Vector}
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
 * The allocateLayerWeights method returns a new Matrix with random weights.
 *
 * @param row    Number of rows.
 * @param column Number of columns.
 * @return Matrix with random weights.
 */
Matrix_ptr allocate_layer_weights(int row, int column, int seed) {
    return create_matrix2(row, column, -0.01, +0.01, seed);
}

/**
 * Frees neural network model
 * @param neural_network Neural network model
 */
void free_neural_network_model(Neural_network_model_ptr neural_network) {
    free_array_list(neural_network->class_labels, NULL);
    free_(neural_network);
}

/**
 * Loads neural network model from input file
 * @param input_file Input file
 * @return Neural network model
 */
Neural_network_model_ptr create_neural_network_model2(FILE *input_file) {
    Neural_network_model_ptr result = malloc_(sizeof(Neural_network_model), "create_neural_network_model2");
    fscanf(input_file, "%d%d", &(result->K), &(result->d));
    result->class_labels = create_array_list();
    for (int i = 0; i < result->K; i++){
        char class_label[MAX_LINE_LENGTH];
        fscanf(input_file, "%s", class_label);
        array_list_add(result->class_labels, class_label);
    }
    return result;
}

/**
 * The calculateHidden method takes a Vector input and Matrix weights, It multiplies the weights
 * Matrix with given input Vector than applies the sigmoid function and returns the result.
 *
 * @param input   Vector to multiply weights.
 * @param weights Matrix is multiplied with input Vector.
 * @return Result of sigmoid function.
 */
Vector_ptr calculate_hidden(const Vector *input, const Matrix *weights, Activation_function activation_function) {
    Vector_ptr z = multiply_with_vector_from_right(weights, input);
    switch (activation_function) {
        case SIGMOID:
            sigmoid_of_vector(z);
            break;
        case TANH:
            tanh_of_vector(z);
            break;
        case RELU:
            relu_of_vector(z);
            break;
    }
    return z;
}

/**
 * The calculateOneMinusHidden method takes a {@link java.util.Vector} as input. It creates a Vector of ones and
 * returns the difference between given Vector.
 *
 * @param hidden Vector to find difference.
 * @return Returns the difference between ones Vector and input Vector.
 * @throws VectorSizeMismatch Return: Number of items in both vectors must be the same.
 */
Vector_ptr calculate_one_minus_hidden(const Vector *hidden) {
    Vector_ptr one = create_vector2(hidden->size, 1.0);
    Vector_ptr result = vector_difference(one, hidden);
    free_vector(one);
    return result;
}

/**
 * The calculateForwardSingleHiddenLayer method takes two matrices W and V. First it multiplies W with x, then
 * multiplies V with the result of the previous multiplication.
 *
 * @param W Matrix to multiply with x.
 * @param V Matrix to multiply.
 * @param activationFunction Activation function.
 */
void calculate_forward_single_hidden_layer(Neural_network_model_ptr neural_network, const Matrix *W, const Matrix *V,
                                           Activation_function activation_function) {
    Vector_ptr hidden = calculate_hidden(neural_network->x, W, activation_function);
    Vector_ptr hidden_biased = biased(hidden);
    free_vector(hidden);
    neural_network->y = multiply_with_vector_from_right(V, hidden_biased);
    free_vector(hidden_biased);
}

/**
 * The predict method takes an Instance as an input, converts it to a Vector and calculates the Matrix y by
 * multiplying Matrix W with Vector x. Then it returns the class label which has the maximum y value.
 *
 * @param instance Instance to predict.
 * @return The class lable which has the maximum y.
 */
char *predict_neural_network(Neural_network_model_ptr neural_network_model, const Instance *instance, const void *meta_model,
                             void (*calculate_output)(const void *)) {
    neural_network_model->x = create_input_vector(instance);
    calculate_output(meta_model);
    char* class_label = array_list_get(neural_network_model->class_labels, max_index_of_vector(neural_network_model->y));
    free_vector(neural_network_model->y);
    free_vector(neural_network_model->x);
    return class_label;
}

/**
 * Calculates the posterior probability distribution for the given instance according to neural network model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr
predict_probability_neural_network(Neural_network_model_ptr neural_network_model, const Instance *instance, const void *meta_model,
                                   void (*calculate_output)(const void *)) {
    neural_network_model->x = create_input_vector(instance);
    calculate_output(meta_model);
    Hash_map_ptr result = create_string_hash_map();
    for (int i = 0; i < neural_network_model->class_labels->size; i++){
        double *probability = malloc_(sizeof(double), "predict_probability_neural_network");
        *probability = get_value(neural_network_model->y, i);
        hash_map_insert(result, array_list_get(neural_network_model->class_labels, i), probability);
    }
    free_vector(neural_network_model->y);
    free_vector(neural_network_model->x);
    return result;
}

/**
 * Reads activation function from input file
 * @param input_file Input file
 * @return Activation function
 */
Activation_function get_activation_function(FILE *input_file) {
    char line[MAX_LINE_LENGTH];
    fscanf(input_file, "%s", line);
    if (strcmp(line, "TANH") == 0){
        return TANH;
    } else {
        if (strcmp(line, "RELU") == 0){
            return RELU;
        } else {
            return SIGMOID;
        }
    }
}
