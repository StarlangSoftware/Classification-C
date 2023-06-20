//
// Created by Olcay Taner YILDIZ on 5.06.2023.
//

#ifndef CLASSIFICATION_ATTRIBUTETYPE_H
#define CLASSIFICATION_ATTRIBUTETYPE_H

enum attribute_type{
    /**
 * Continuous Attribute
 */
    CONTINUOUS,
    /**
     * Discrete Attribute
     */
    DISCRETE,
    /**
     * Binary Attribute
     */
    BINARY,
    /**
     * Discrete Indexed Attribute is used to store the indices.
     */
    DISCRETE_INDEXED
};

typedef enum attribute_type Attribute_type;

#endif //CLASSIFICATION_ATTRIBUTETYPE_H
