//
// Created by Olcay Taner YILDIZ on 6.06.2023.
//

#ifndef CLASSIFICATION_LINEARPERCEPTRONPARAMETER_H
#define CLASSIFICATION_LINEARPERCEPTRONPARAMETER_H

struct linear_perceptron_parameter{
    int seed;
    double learning_rate;
    double eta_decrease;
    double cross_validation_ratio;
    int epoch;
};

typedef struct linear_perceptron_parameter Linear_perceptron_parameter;

typedef Linear_perceptron_parameter *Linear_perceptron_parameter_ptr;

Linear_perceptron_parameter_ptr create_linear_perceptron_parameter(int seed, double learningRate, double etaDecrease, double crossValidationRatio, int epoch);

void free_linear_perceptron_parameter(Linear_perceptron_parameter_ptr linear_perceptron_parameter);

#endif //CLASSIFICATION_LINEARPERCEPTRONPARAMETER_H
