#include "gtest/gtest.h"

extern "C" {
#include "vector.h" // Include your vector header
}

TEST(VectorTest, Initialization) {
    vector v;
    vector_init(&v, 10, sizeof(int));
    EXPECT_EQ(vector_size(&v), (size_t)0);
    EXPECT_EQ(vector_capacity(&v), (size_t)10);
    EXPECT_TRUE(vector_empty(&v));

    vector_free(&v);
}

TEST(VectorTest, AddAndGet) {
    vector v;
    vector_init(&v, 2, sizeof(int));
    int val1 = 42;
    int val2 = 100;

    vector_add(&v, &val1);
    vector_add(&v, &val2);

    EXPECT_EQ(vector_size(&v), (size_t)2);
    EXPECT_EQ(vector_capacity(&v), (size_t)2);

    int retrieved = 0;
    vector_get(&v, &retrieved, 0);
    EXPECT_EQ(retrieved, 42);
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 100);

    vector_free(&v);
}

TEST(VectorTest, Resize) {
    vector v;
    vector_init(&v, 2, sizeof(int));
    int values[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        vector_add(&v, &values[i]);
    }

    EXPECT_EQ(vector_size(&v), (size_t)4);
    // Capacity likely doubled from 2 to 4
    EXPECT_EQ(vector_capacity(&v), (size_t)4);

    vector_free(&v);
}

TEST(VectorTest, Set) {
    vector v;
    vector_init(&v, 3, sizeof(int));
    int values[] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        vector_add(&v, &values[i]);

    int newVal = 99;
    vector_set(&v, 1, &newVal);
    int retrieved = 0;
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 99);

    vector_free(&v);
}

TEST(VectorTest, Remove) {
    vector v;
    vector_init(&v, 3, sizeof(int));
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++)
        vector_add(&v, &values[i]);

    vector_remove(&v); // removes last element (30)
    EXPECT_EQ(vector_size(&v), (size_t)2);

    int retrieved = 0;
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 20);

    vector_free(&v);
}

TEST(VectorTest, InsertElement) {
    vector v;
    vector_init(&v, 3, sizeof(int));
    int values[] = {10, 20, 30};
    for (int i = 0; i < 3; i++)
        vector_add(&v, &values[i]);

    int newVal = 15;
    vector_insert_element(&v, 1, &newVal);

    // Now vector should be [10, 15, 20, 30]
    EXPECT_EQ(vector_size(&v), (size_t)4);

    int retrieved = 0;
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 15);
    vector_get(&v, &retrieved, 2);
    EXPECT_EQ(retrieved, 20);

    vector_free(&v);
}

TEST(VectorTest, RemoveElement) {
    vector v;
    vector_init(&v, 5, sizeof(int));
    int values[] = {5, 10, 15, 20, 25};
    for (int i = 0; i < 5; i++)
        vector_add(&v, &values[i]);

    // Remove element at index 2 (value 15)
    vector_remove_element(&v, 2);

    // Now vector should be [5, 10, 20, 25]
    EXPECT_EQ(vector_size(&v), (size_t)4);

    int retrieved = 0;
    vector_get(&v, &retrieved, 2);
    EXPECT_EQ(retrieved, 20);

    vector_free(&v);
}

static int compare_ints(const void* a,const void* b) {
    int ai = *(int*)a;
    int bi = *(int*)b;
    if (ai < bi) return -1;
    else if (ai > bi) return 1;
    return 0;
}

TEST(VectorTest, Sort) {
    vector v;
    vector_init(&v, 5, sizeof(int));
    int values[] = {20, 5, 25, 10, 15};
    for (int i = 0; i < 5; i++)
        vector_add(&v, &values[i]);

    vector_sort(&v, compare_ints);

    int retrieved = 0;
    for (int i = 0; i < 5; i++) {
        vector_get(&v, &retrieved, i);
        // After sorting: [5, 10, 15, 20, 25]
        EXPECT_EQ(retrieved, (i+1)*5);
    }

    vector_free(&v);
}
