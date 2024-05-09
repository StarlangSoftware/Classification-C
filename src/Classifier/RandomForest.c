//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#include <Memory/Memory.h>
#include "RandomForest.h"
#include "../Parameter/RandomForestParameter.h"
#include "../Model/DecisionTree/DecisionTree.h"
#include "../Model/TreeEnsembleModel.h"
#include "Bagging.h"

/**
 * Training algorithm for random forest classifier. Basically the algorithm creates K distinct decision trees from
 * K bootstrap samples of the original training set.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the bagging trees algorithm. ensembleSize returns the number of trees in the random forest.
 */
Classifier_ptr train_random_forest(Instance_list_ptr train_set, const void *parameter) {
    Classifier_ptr result = malloc_(sizeof(Classifier), "train_random_forest");
    Random_forest_parameter_ptr random_forest_parameter = (Random_forest_parameter_ptr) parameter;
    int forest_size = random_forest_parameter->ensemble_size;
    Array_list_ptr forest = create_array_list();
    for (int i = 0; i < forest_size; i++){
        Bootstrap_ptr bootstrap = bootstrap_instance_list(train_set, i);
        Instance_list_ptr list = create_instance_list3(get_sample(bootstrap));
        array_list_add(forest, create_decision_tree(create_decision_node(list, create_decision_condition4(), random_forest_parameter, false)));
        free_(list);
        free_bootstrap(bootstrap, NULL);
    }
    result->model = create_tree_ensemble_model(forest);
    result->train = train_random_forest;
    result->predict_probability = predict_probability_ensemble;
    result->predict = predict_ensemble;
    return result;
}

/**
 * Loads the random forest model from an input file.
 * @param fileName File name of the random forest model.
 */
Classifier_ptr load_random_forest(const char *file_name) {
    Classifier_ptr result = load_bagging(file_name);
    result->train = train_random_forest;
    return result;
}

/**
 * Frees memory allocated for random forest model.
 * @param random_forest Random forest model
 */
void free_random_forest(Classifier_ptr random_forest) {
    free_tree_ensemble_model(random_forest->model);
    free_(random_forest);
}
