# Dynamic Array (Vector) - Programmer's Workshop 2024

## Project Description

This project provides a simple and efficient implementation of a dynamic array (commonly known as a vector) in C. Developed during the Programmer's Workshop 2024 at the University of Gdańsk (Informatics, 1st semester) by **Filip Hoang** with assistance from Codium and ChatGPT, it aims to serve as a flexible and easily extensible building block for various projects requiring dynamic contiguous storage.

A dynamic array allows for resizing at runtime, ensuring that elements can be appended without prior knowledge of the required capacity. Although the operations provided are convenient and efficient on average, some operations may incur a higher cost than their static-array counterparts—particularly those that trigger resizing or involve shifting elements.

## Features

- **Initialization with Custom Capacity and Element Size**: Create a vector with a specified initial capacity and the size of each element.
- **Dynamic Resizing**: Adjusts capacity automatically as elements are added.
- **Random Access in Constant Time**: Read and write any element using direct indexing.
- **Insertion and Removal**: Add or remove elements from the end in amortized constant time; insert or remove elements at arbitrary positions.
- **Swapping and Sorting**: Interchange the positions of two elements and perform sorting with a custom comparator.
- **Memory Management**: Easily clear or free the underlying storage.

## Functions and Time Complexity

- **Initialization**
  - `void_init(vector* vector, size_t capacity, size_t element_bytes)` – O(1)  
    Allocates memory and sets up an empty vector with the given capacity and element size.

- **Adding Elements**
  - `vector_add(vector* vector, void* value)` – Amortized O(1)  
    Appends a new element to the end. If capacity is reached, the vector resizes, resulting in an O(n) operation at that specific moment. Over many insertions, the amortized cost remains O(1).

- **Accessing and Modifying Elements**
  - `vector_get(vector* vector, void* value, size_t index)` – O(1)  
    Retrieves the element at the specified index.
  - `vector_set(vector* vector, size_t index, void* value)` – O(1)  
    Overwrites the element at the given index with a new value.

- **Removing and Resizing**
  - `vector_remove(vector* vector)` – O(1)  
    Removes the last element.
  - `vector_resize(vector* vector, size_t new_capacity)` – O(n)  
    Adjusts the vector’s capacity, copying existing elements into newly allocated space.
  - `vector_remove_element(vector* vector, size_t index)` – O(n)  
    Removes an element at the specified index. All elements following it are shifted.
  
- **Insertion**
  - `vector_insert_element(vector* vector, size_t index, void* value)` – O(n)  
    Inserts a new element at the specified index, shifting elements as needed.

- **Management and Queries**
  - `vector_free(vector* vector)` – O(1)  
    Frees the memory associated with the vector and resets its fields.
  - `vector_clear(vector* vector)` – O(1)  
    Resets the size to zero, effectively clearing the vector while retaining allocated capacity.
  - `vector_size(vector* vector)` – O(1)  
    Returns the current number of elements.
  - `vector_capacity(vector* vector)` – O(1)  
    Returns the current allocated capacity.
  - `vector_empty(vector* vector)` – O(1)  
    Checks if the vector is empty.

- **Utilities**
  - `vector_swap(vector* vector, size_t index1, size_t index2)` – O(1)  
    Swaps the elements at the two specified indices.
  - `vector_contains(vector* vector, void* value, int (*compare)(void*, void*))` – O(n)  
    Checks if the vector contains the specified value, using a custom comparator.
  - `vector_sort(vector* vector, int (*compare)(void*, void*))` – O(n log n)  
    Sorts the elements using `qsort` and a provided comparator.

## Design and Implementation Details

Internally, the vector manages a continuous block of memory that stores elements in sequence. The memory allocation is performed using `malloc`, `realloc`, and `free`. As the vector grows beyond its current capacity, `realloc` and `memcpy` is used to allocate more space, copying existing data to the new buffer as necessary. This design ensures that element access by index remains O(1), while append operations are amortized O(1).

Customizable element size allows this vector to store any data type, though manual casting may be required when dealing with element pointers. Comparator functions can be supplied for operations like searching (`vector_contains`) and sorting (`vector_sort`).

## License

This project is released under the [MIT License](LICENSE). Users are free to use, modify, and distribute this code under the terms of the MIT License.
