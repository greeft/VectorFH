#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h> // for size_t

typedef struct {
    void* ptr;
    size_t size;
    size_t capacity;
    size_t element_bytes;
} vector;

/* Initialization */
void vector_init(vector* vector, size_t capacity, size_t element_bytes);

/* Element Access and Modification */
void vector_add(vector* vector, void* value);
void vector_get(vector* vector, void* value, size_t index);
void vector_set(vector* vector, size_t index, void* value);

/* Removal and Resizing */
void vector_remove(vector* vector);
void vector_resize(vector* vector, size_t new_capacity);
vector vector_free(vector* vector);
void vector_clear(vector* vector);

/* Queries */
size_t vector_size(vector* vector);
size_t vector_capacity(vector* vector);
int vector_empty(vector* vector);
int vector_contains(vector* vector, void* value, int (*compare)(void*, void*));

/* Additional Operations */
void vector_swap(vector* vector, size_t index1, size_t index2);
void vector_remove_element(vector* vector, size_t index);
void vector_insert_element(vector* vector, size_t index, void* value);
void vector_sort(vector* vector, int (*compare)(void*, void*));

#endif /* VECTOR_H */
