//
// Created by Olcay Taner YILDIZ on 7.06.2023.
//

#ifndef CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H
#define CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H

struct classification_performance{
    double accuracy;
};

typedef struct classification_performance Classification_performance;

typedef Classification_performance *Classification_performance_ptr;

Classification_performance_ptr create_classification_performance(double accuracy);

#endif //CLASSIFICATION_CLASSIFICATIONPERFORMANCE_H
