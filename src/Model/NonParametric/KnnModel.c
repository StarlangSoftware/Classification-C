//
// Created by Olcay Taner YILDIZ on 24.06.2023.
//

#include <Memory/Memory.h>
#include "KnnModel.h"
#include "KnnInstance.h"
#include "../../Parameter/KnnParameter.h"
#include "../../DistanceMetric/EuclidianDistance.h"

/**
 * Constructor that sets the data InstanceList, k value and the DistanceMetric.
 *
 * @param data           InstanceList input.
 * @param k              K value.
 * @param distance_metric DistanceMetric input.
 */
Knn_model_ptr create_knn_model(Instance_list_ptr data, int k,
                               double (*distance_metric)(const Instance *, const Instance *, const void *)) {
    Knn_model_ptr result = malloc_(sizeof(Knn_model));
    result->data = data;
    result->k = k;
    result->distance_metric = distance_metric;
    return result;
}

/**
 * Frees memory allocated for K-nearest neighbor model.
 * @param knn_model K-nearest neighbor model.
 */
void free_knn_model(Knn_model_ptr knn_model) {
    free_(knn_model);
}

/**
 * The nearestNeighbors method takes an Instance as an input. First it gets the possible class labels, then loops
 * through the data InstanceList and creates new ArrayList of KnnInstances and adds the corresponding data with
 * the distance between data and given instance. After sorting this newly created ArrayList, it loops k times and
 * returns the first k instances as an InstanceList.
 *
 * @param knn_model Knn model
 * @param instance Instance to find nearest neighbors/
 * @return The first k instances which are nearest to the given instance as an InstanceList.
 */
Instance_list_ptr nearest_neighbors(const Knn_model* knn_model, const Instance *instance) {
    Array_list_ptr all_instances = create_array_list();
    for (int i = 0; i < size_of_instance_list(knn_model->data); i++){
        Instance_ptr current = get_instance(knn_model->data, i);
        array_list_add(all_instances, create_knn_instance(current, knn_model->distance_metric(current, instance, NULL)));
    }
    array_list_sort(all_instances, (int (*)(const void *, const void *)) compare_knn_instance);
    Instance_list_ptr sub_list = create_instance_list();
    for (int i = 0; i < knn_model->k; i++){
        Knn_instance_ptr knn_instance = array_list_get(all_instances, i);
        add_instance(sub_list, knn_instance->instance);
    }
    free_array_list(all_instances, (void (*)(void *)) free_knn_instance);
    return sub_list;
}

/**
 * The predict method takes an Instance as an input and finds the nearest neighbors of given instance. Then
 * it returns the first possible class label as the predicted class.
 *
 * @param model Knn model
 * @param instance Instance to make prediction.
 * @return The first possible class label as the predicted class.
 */
char *predict_knn(const void *model, const Instance *instance) {
    Knn_model_ptr knn_model = (Knn_model_ptr) model;
    Instance_list_ptr neighbors = nearest_neighbors(knn_model, instance);
    Array_list_ptr class_labels = get_class_labels(neighbors);
    char* predicted_class = get_maximum(class_labels);
    free_array_list(class_labels, NULL);
    free_instance_list2(neighbors);
    return predicted_class;
}

/**
 * Calculates the posterior probability distribution for the given instance according to K-means model.
 * @param model Knn model
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
Hash_map_ptr predict_probability_knn(const void *model, const Instance *instance) {
    Knn_model_ptr knn_model = (Knn_model_ptr) model;
    Hash_map_ptr result;
    Instance_list_ptr neighbors = nearest_neighbors(knn_model, instance);
    Discrete_distribution_ptr discrete_distribution = class_distribution(neighbors);
    result = get_probability_distribution(discrete_distribution);
    free_discrete_distribution(discrete_distribution);
    free_instance_list2(neighbors);
    return result;
}

/**
 * Loads a K-nearest neighbor model from an input model file.
 * @param file_name Model file name.
 */
Knn_model_ptr create_knn_model2(const char *file_name) {
    Knn_model_ptr result = malloc_(sizeof(Knn_model));
    FILE* input_file = fopen(file_name, "r");
    fscanf(input_file, "%d", &(result->k));
    result->data = create_instance_list4(input_file);
    result->distance_metric = euclidian_distance;
    fclose(input_file);
    return result;
}

/**
 * Training algorithm for K-nearest neighbor classifier.
 *
 * @param train_set   Training data given to the algorithm.
 * @param parameter K: k parameter of the K-nearest neighbor algorithm
 *                   distanceMetric: distance metric used to calculate the distance between two instances.
 */
Model_ptr train_knn(Instance_list_ptr train_set, const void *parameter) {
    Model_ptr result = malloc_(sizeof(Model));
    result->model = create_knn_model(train_set, ((Knn_parameter_ptr)(parameter))->k, ((Knn_parameter_ptr)(parameter))->distance_function);
    result->train = train_knn;
    result->predict = predict_knn;
    result->predict_probability = predict_probability_knn;
    return result;
}

/**
 * Loads the K-nearest neighbor model from an input file.
 * @param file_name File name of the K-nearest neighbor model.
 */
Model_ptr load_knn(const char *file_name) {
    Model_ptr result = malloc_(sizeof(Model));
    result->model = create_knn_model2(file_name);
    result->train = train_knn;
    result->predict = predict_knn;
    result->predict_probability = predict_probability_knn;
    return result;
}

/**
 * Frees memory allocated for K-nearest neighbor model
 * @param knn K-nearest neighbor model
 */
void free_knn(Model_ptr knn) {
    free_knn_model(knn->model);
    free_(knn);
}
