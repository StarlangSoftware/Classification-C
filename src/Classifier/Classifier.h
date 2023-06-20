//
// Created by Olcay Taner YILDIZ on 20.06.2023.
//

#ifndef CLASSIFICATION_CLASSIFIER_H
#define CLASSIFICATION_CLASSIFIER_H

struct classifier{
    void* model;
};

typedef struct classifier Classifier;

typedef Classifier *Classifier_ptr;

#endif //CLASSIFICATION_CLASSIFIER_H
