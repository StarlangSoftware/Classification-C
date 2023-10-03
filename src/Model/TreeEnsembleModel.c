//
// Created by Olcay Taner YILDIZ on 14.07.2023.
//

#include <stdlib.h>
#include "TreeEnsembleModel.h"
#include "DecisionTree/DecisionTree.h"

/**
 * A constructor which sets the vector of DecisionTree with given input.
 *
 * @param forest An vector of DecisionTree.
 */
Tree_ensemble_model_ptr create_tree_ensemble_model(Array_list_ptr forest) {
    Tree_ensemble_model_ptr result = malloc(sizeof(Tree_ensemble_model));
    result->forest = forest;
    return result;
}

Tree_ensemble_model_ptr create_tree_ensemble_model2(const char *file_name) {
    Tree_ensemble_model_ptr result = malloc(sizeof(Tree_ensemble_model));
    result->forest = create_array_list();
    FILE* input_file = fopen(file_name, "r");
    int size;
    fscanf(input_file, "%d", &size);
    for (int i = 0; i < size; i++){
        Decision_tree_ptr tree = create_decision_tree2(input_file);
        array_list_add(result->forest, tree);
    }
    fclose(input_file);
    return result;
}

void free_tree_ensemble_model(Tree_ensemble_model_ptr model) {
    free_array_list(model->forest, (void (*)(void *)) free_decision_tree);
    free(model);
}

/**
 * The predict method takes an Instance as an input and loops through the ArrayList of DecisionTrees.
 * Makes prediction for the items of that ArrayList and returns the maximum item of that ArrayList.
 *
 * @param instance Instance to make prediction.
 * @return The maximum prediction of a given Instance.
 */
char *predict_ensemble(const void *model, const Instance *instance) {
    Tree_ensemble_model_ptr ensemble = (Tree_ensemble_model_ptr) model;
    Discrete_distribution_ptr distribution = create_discrete_distribution();
    for (int i = 0; i < ensemble->forest->size; i++){
        Decision_tree_ptr tree = array_list_get(ensemble->forest, i);
        add_item(distribution, predict_tree(tree, instance));
    }
    char *result = get_max_item(distribution);
    free_discrete_distribution(distribution);
    return result;
}

Hash_map_ptr predict_probability_ensemble(const void *model, const Instance *instance) {
    Tree_ensemble_model_ptr ensemble = (Tree_ensemble_model_ptr) model;
    Discrete_distribution_ptr distribution = create_discrete_distribution();
    for (int i = 0; i < ensemble->forest->size; i++){
        Decision_tree_ptr tree = array_list_get(ensemble->forest, i);
        add_item(distribution, predict_tree(tree, instance));
    }
    Hash_map_ptr result = get_probability_distribution(distribution);
    free_discrete_distribution(distribution);
    return result;
}
