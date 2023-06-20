//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#ifndef CLASSIFICATION_PERFORMANCE_H
#define CLASSIFICATION_PERFORMANCE_H

struct performance{
    double error_rate;
};

typedef struct performance Performance;

typedef Performance *Performance_ptr;

Performance_ptr create_performance(double error_rate);

void free_performance(Performance_ptr performance);

#endif //CLASSIFICATION_PERFORMANCE_H
