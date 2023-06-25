//
// Created by Olcay Taner YILDIZ on 24.06.2023.
//

#include <stdlib.h>
#include "Knn_model.h"
#include "KnnInstance.h"
#include "../Classifier/Classifier.h"
#include "../DistanceMetric/EuclidianDistance.h"

/**
 * Constructor that sets the data {@link InstanceList}, k value and the {@link DistanceMetric}.
 *
 * @param data           {@link InstanceList} input.
 * @param k              K value.
 * @param distanceMetric {@link DistanceMetric} input.
 */
Knn_model_ptr create_knn_model(Instance_list_ptr data, int k,
                               double (*distance_metric)(const Instance *, const Instance *, const void *)) {
    Knn_model_ptr result = malloc(sizeof(Knn_model));
    result->data = data;
    result->k = k;
    result->distance_metric = distance_metric;
    return result;
}

void free_knn_model(Knn_model_ptr knn_model) {
    free(knn_model);
}

/**
 * The nearestNeighbors method takes an {@link Instance} as an input. First it gets the possible class labels, then loops
 * through the data {@link InstanceList} and creates new {@link ArrayList} of {@link KnnInstance}s and adds the corresponding data with
 * the distance between data and given instance. After sorting this newly created ArrayList, it loops k times and
 * returns the first k instances as an {@link InstanceList}.
 *
 * @param instance {@link Instance} to find nearest neighbors/
 * @return The first k instances which are nearest to the given instance as an {@link InstanceList}.
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
    free_array_list(all_instances, NULL);
    return sub_list;
}

/**
 * The predict method takes an {@link Instance} as an input and finds the nearest neighbors of given instance. Then
 * it returns the first possible class label as the predicted class.
 *
 * @param instance {@link Instance} to make prediction.
 * @return The first possible class label as the predicted class.
 */
char *predict_knn(const void *model, const Instance *instance) {
    Knn_model_ptr knn_model = (Knn_model_ptr) model;
    Instance_list_ptr neighbors = nearest_neighbors(knn_model, instance);
    char* predicted_class = get_maximum(get_class_labels(neighbors));
    free(neighbors);
    return predicted_class;
}

Hash_map_ptr predict_probability_knn(const void *model, const Instance *instance) {
    Knn_model_ptr knn_model = (Knn_model_ptr) model;
    Hash_map_ptr result;
    Instance_list_ptr neighbors = nearest_neighbors(knn_model, instance);
    Discrete_distribution_ptr discrete_distribution = class_distribution(neighbors);
    result = get_probability_distribution(discrete_distribution);
    free(discrete_distribution);
    free(neighbors);
    return result;
}

Knn_model_ptr create_knn_model2(const char *file_name) {
    Knn_model_ptr result = malloc(sizeof(Knn_model));
    FILE* input_file = fopen(file_name, "r");
    fscanf(input_file, "%d", &(result->k));
    result->data = create_instance_list4(input_file);
    result->distance_metric = euclidian_distance;
    fclose(input_file);
    return result;
}
