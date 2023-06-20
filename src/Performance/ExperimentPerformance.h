//
// Created by Olcay Taner YILDIZ on 13.06.2023.
//

#ifndef CLASSIFICATION_EXPERIMENTPERFORMANCE_H
#define CLASSIFICATION_EXPERIMENTPERFORMANCE_H

#include <ArrayList.h>
#include "Performance.h"

struct experiment_performance{
    Array_list_ptr results;
};

typedef struct experiment_performance Experiment_performance;

typedef Experiment_performance *Experiment_performance_ptr;

Experiment_performance_ptr create_experiment_performance();

Experiment_performance_ptr create_experiment_performance2(const char* file_name);

void add_performance(Experiment_performance_ptr experiment_performance, Performance_ptr performance);

int number_of_experiments(const Experiment_performance* experiment_performance);

double get_error_rate(const Experiment_performance* experiment_performance, int index);

Performance_ptr mean_performance(const Experiment_performance* experiment_performance);

Performance_ptr standard_deviation_performance(const Experiment_performance* experiment_performance);

#endif //CLASSIFICATION_EXPERIMENTPERFORMANCE_H
