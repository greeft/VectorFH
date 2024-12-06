/*==============================================================
# Dynamic Array (Vector) - Programmer's Workshop 2024
==============================================================*/

/*==============================================================
## Project Description
   This project provides a simple and efficient implementation of 
   a dynamic array (commonly known as a vector) in C. Developed 
   during the Programmer's Workshop 2024 at the University of 
   Gdańsk (Informatics, 1st semester) by Filip Hoang with 
   assistance from Codium and ChatGPT, it serves as a flexible 
   building block for projects requiring dynamic contiguous 
   storage.

   Dynamic arrays allow resizing at runtime, making it possible 
   to append elements without prior capacity knowledge. While 
   convenient and generally efficient, certain operations—like 
   those causing frequent resizing or shifting—may be less 
   efficient than using static arrays.
==============================================================*/

/*==============================================================
## Features
 - Initialization with Custom Capacity and Element Size
 - Dynamic Resizing
 - Random Access in Constant Time
 - Insertion and Removal at arbitrary positions
 - Sorting with custom comparator
 - Memory Management: Clear and Free easily
==============================================================*/

/*==============================================================
## Functions and Time Complexity

### Initialization
 - vector_init(vector* vector, size_t capacity, size_t element_bytes)   O(1)
   Allocates memory and sets up an empty vector.

### Adding Elements
 - vector_add(vector* vector, void* value)                            Amortized O(1)
   Appends a new element to the end. Triggers resize when capacity is reached.

### Accessing and Modifying Elements
 - vector_get(vector* vector, void* value, size_t index)              O(1)
   Retrieves the element at the given index.
 - vector_set(vector* vector, size_t index, void* value)              O(1)
   Overwrites the element at the specified index.

### Removing and Resizing
 - vector_remove(vector* vector)                                       O(1)
   Removes the last element.
 - vector_resize(vector* vector, size_t new_capacity)                  O(n)
   Resizes the vector, reallocating and copying elements.
 - vector_remove_element(vector* vector, size_t index)                 O(n)
   Removes an element at a specified index, shifting subsequent elements.

### Insertion
 - vector_insert_element(vector* vector, size_t index, void* value)    O(n)
   Inserts a new element at a given index, shifting subsequent elements.

### Management and Queries
 - vector_free(vector* vector)                                         O(1)
   Frees the memory and resets the vector’s fields.
 - vector_clear(vector* vector)                                        O(1)
   Clears the vector without freeing memory, size=0.
 - vector_size(vector* vector)                                         O(1)
   Returns the number of elements.
 - vector_capacity(vector* vector)                                     O(1)
   Returns the allocated capacity.
 - vector_empty(vector* vector)                                        O(1)
   Checks if the vector is empty.

### Utilities
 - vector_swap(vector* vector, size_t index1, size_t index2)           O(1)
   Swaps two elements.
 - vector_contains(vector* vector, void* value, int (*compare)(...))   O(n)
   Checks if a given value exists, using a custom comparator.
 - vector_sort(vector* vector, int (*compare)(...))                    O(n log n)
   Sorts the vector using qsort and a custom comparator.
==============================================================*/

/*==============================================================
## Design and Implementation Details
   The vector internally manages a continuous block of memory 
   using malloc, realloc,free,memcpy and memmove. When capacity is exceeded, 
   resizing occurs, which involves copying all elements into 
   a larger block of memory.

   By specifying element size at initialization, this vector 
   can hold any data type. Comparator functions enable custom 
   searching and sorting behaviors.
==============================================================*/

/*==============================================================
## License
   This project is released under the MIT License. Users are free 
   to use, modify, and distribute this code under these terms.
==============================================================*/
