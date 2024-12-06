#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
/*/
#ifdef vectormcr

#define init vector_init
#define add vector_add
#define get vector_get
#define set vector_set
#define cap vector_capacity
#define free vector_free
#define size vector_size
#define empty vector_empty
#define swap vector_swap
#define rm vector_remove_element

#endif vectormcr

/*/
typedef struct {
    void* ptr;
    size_t size;
    size_t capacity;
    size_t element_bytes;
}vector;
void vector_init(vector* vector, size_t capacity,size_t element_bytes)
{
    vector->ptr=malloc(capacity*element_bytes);
    vector->capacity=capacity;
    vector->element_bytes=element_bytes;
    vector->size=0;
    if(vector->ptr==NULL)
    {
        printf("Error: Memory Allocation failed");
        exit(1);
    }
}
void vector_add(vector* vector, void* value)
{
    if(vector->size==vector->capacity)
    {
        vector->capacity*=2;
        vector->ptr=realloc(vector->ptr,vector->capacity*vector->element_bytes);
        if(vector->ptr==NULL)
        {
            printf("Error: Memory Allocation failed");
            exit(1);
        }
    }
    memcpy(vector->ptr+(vector->size*vector->element_bytes),value,vector->element_bytes);
    vector->size++;
}
void vector_get(vector* vector, void* value, size_t index)
{
    memcpy(value,vector->ptr+(index*vector->element_bytes),vector->element_bytes);

}
void vector_set(vector* vector, size_t index, void* value)
{
    memcpy(vector->ptr+(index*vector->element_bytes),value,vector->element_bytes);
}
void vector_remove(vector* vector)
{
    vector->size--;
}
void vector_resize(vector* vector, size_t new_capacity)
{
    vector->capacity=new_capacity;
    vector->ptr=realloc(vector->ptr,vector->capacity*vector->element_bytes);
    if(vector->ptr==NULL)
    {
        printf("Error: Memory Allocation failed");
        exit(1);
    }
}

vector vector_free(vector* vector)
{
    free(vector->ptr);
    vector->ptr=NULL;
    vector->size=0;
    vector->capacity=0;
    vector->element_bytes=0;
}

void vector_clear(vector* vector)
{
    vector->size=0;
}

int vector_size(vector* vector)
{
    return vector->size;
}

int vector_capacity(vector* vector)
{
    return vector->capacity;
}

int vector_empty(vector* vector)
{
    return vector->size==0;
}
int vector_contains(vector* vector, void* value,int (*compare)(const void*, const void*))
{
    void *temp_value=malloc(vector->element_bytes);
    if(temp_value==NULL)
    {
        printf("Error: Memory Allocation failed");
        exit(1);
    }
    for(int i=0;i<vector->size;i++)
    {
        vector_get(vector,temp_value,i);
        if(compare((char*)temp_value,(char*)value)==0)
        {
            return 1;
        }
    }
    free(temp_value);
    return 0;
}

void vector_swap(vector* vector,size_t index1, size_t index2)
{
    if (index1 >= vector->size || index2 >= vector->size) {
    printf("Error: Index out of bounds\n");
    exit(1);
    }
    void* temp=malloc(vector->element_bytes);
    if(temp==NULL)
    {
        printf("Error: Memory Allocation failed");
        exit(1);
    }
    memcpy(temp,vector->ptr+(index1*vector->element_bytes),vector->element_bytes);
    memcpy(vector->ptr+(index1*vector->element_bytes),vector->ptr+(index2*vector->element_bytes),vector->element_bytes);
    memcpy(vector->ptr+(index2*vector->element_bytes),temp,vector->element_bytes);
    free(temp);
}
void vector_remove_element(vector* vector, size_t index)
{
    if(index>=vector->size)
    {
        printf("Error: Index out of bounds");
        exit(1);
    }
    if(index==vector->size-1)
    {
        vector_remove(vector);
        return;
    }
    memmove((char*)vector->ptr+(index*vector->element_bytes),(char*)vector->ptr+((index+1)*vector->element_bytes),(vector->size-index-1)*vector->element_bytes);
    vector->size--;
}

void vector_insert_element(vector* vector, size_t index, void* value)
{
    if(index>vector->size)
    {
        printf("Error: Index out of bounds");
        exit(1);
    }
    if(vector->size==vector->capacity)
    {
        vector->capacity*=2;
        vector->ptr=realloc(vector->ptr,vector->capacity*vector->element_bytes);
        if(vector->ptr==NULL)
        {
            printf("Error: Memory Allocation failed");
            exit(1);
        }
    }
    if(index==vector->size)
    {
        vector_add(vector,value);
        return;
    }
    memmove((char*)vector->ptr+((index+1)*vector->element_bytes),(char*)vector->ptr+(index*vector->element_bytes),(vector->size-index)*vector->element_bytes);
    memcpy(vector->ptr+(index*vector->element_bytes),value,vector->element_bytes);
    vector->size++;
}

void vector_sort(vector* vector, int (*compar)(const void *, const void*))
{
    qsort(vector->ptr,vector->size,vector->element_bytes,compar);
}