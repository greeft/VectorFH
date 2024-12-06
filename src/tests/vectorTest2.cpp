#include "gtest/gtest.h"

extern "C" {
#include "vector.h"
}

static int compare_ints(const void* a,const void* b) {
    int ai = *(int*)a;
    int bi = *(int*)b;
    if (ai < bi) return -1;
    else if (ai > bi) return 1;
    return 0;
}

class VectorTest : public ::testing::Test {
protected:
    vector v;

    void SetUp() override {
        vector_init(&v, 4, sizeof(int));
    }

    void TearDown() override {
        vector_free(&v);
    }
};

/* Basic Operations and Edge Cases */
TEST_F(VectorTest, EmptyOnInitialization) {
    EXPECT_EQ(vector_size(&v), (size_t)0);
    EXPECT_EQ(vector_capacity(&v), (size_t)4);
    EXPECT_TRUE(vector_empty(&v));
}

TEST_F(VectorTest, AddElementsUntilResize) {
    // Initial capacity = 4
    for (int i = 0; i < 10; i++) {
        vector_add(&v, &i);
    }
    EXPECT_EQ(vector_size(&v), (size_t)10);
    EXPECT_GE(vector_capacity(&v), (size_t)10);
}

TEST_F(VectorTest, GetElements) {
    int values[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) {
        vector_add(&v, &values[i]);
    }

    for (int i = 0; i < 4; i++) {
        int retrieved = 0;
        vector_get(&v, &retrieved, i);
        EXPECT_EQ(retrieved, values[i]);
    }
}

TEST_F(VectorTest, SetElements) {
    int values[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) vector_add(&v, &values[i]);

    int newVal = 99;
    vector_set(&v, 2, &newVal);

    int retrieved = 0;
    vector_get(&v, &retrieved, 2);
    EXPECT_EQ(retrieved, 99);
}

TEST_F(VectorTest, RemoveLastElement) {
    int x = 42;
    vector_add(&v, &x);
    EXPECT_EQ(vector_size(&v), (size_t)1);

    vector_remove(&v);
    EXPECT_EQ(vector_size(&v), (size_t)0);
    EXPECT_TRUE(vector_empty(&v));
}

/* Insert and Remove Element at Arbitrary Positions */
TEST_F(VectorTest, InsertAtBeginning) {
    int a = 10, b = 20, c = 30;
    vector_add(&v, &b);
    vector_add(&v, &c);
    vector_insert_element(&v, 0, &a); // Insert at start

    // Expected: [10, 20, 30]
    int retrieved = 0;
    vector_get(&v, &retrieved, 0);
    EXPECT_EQ(retrieved, 10);
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 20);
}

TEST_F(VectorTest, InsertAtEnd) {
    int a = 100, b = 200;
    vector_add(&v, &a);
    vector_insert_element(&v, 1, &b); // Insert at end (since size = 1)
    EXPECT_EQ(vector_size(&v), (size_t)2);

    int retrieved = 0;
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 200);
}

TEST_F(VectorTest, RemoveElementInMiddle) {
    int vals[] = {5,10,15,20};
    for (int i=0; i<4; i++) vector_add(&v, &vals[i]);

    vector_remove_element(&v, 1); // remove element '10'
    // Expected: [5, 15, 20]
    EXPECT_EQ(vector_size(&v), (size_t)3);

    int retrieved = 0;
    vector_get(&v, &retrieved, 1);
    EXPECT_EQ(retrieved, 15);
}

TEST_F(VectorTest, RemoveElementAtStart) {
    int vals[] = {1,2,3};
    for (int i=0; i<3; i++) vector_add(&v,&vals[i]);

    vector_remove_element(&v,0); // remove first element
    // Expected: [2, 3]
    EXPECT_EQ(vector_size(&v), (size_t)2);

    int retrieved;
    vector_get(&v,&retrieved,0);
    EXPECT_EQ(retrieved,2);
}

TEST_F(VectorTest, RemoveElementAtEnd) {
    int vals[] = {7,8,9};
    for (int i=0; i<3; i++) vector_add(&v,&vals[i]);

    vector_remove_element(&v,2); // remove last element '9'
    // Expected: [7,8]
    EXPECT_EQ(vector_size(&v), (size_t)2);
    int retrieved;
    vector_get(&v, &retrieved,1);
    EXPECT_EQ(retrieved,8);
}

/* Clear and Free Operations */
TEST_F(VectorTest, ClearVector) {
    int x = 50;
    vector_add(&v,&x);
    vector_add(&v,&x);

    vector_clear(&v);
    EXPECT_EQ(vector_size(&v),(size_t)0);
    EXPECT_FALSE(vector_empty(&v)==false); // vector_empty should return true now
    EXPECT_TRUE(vector_empty(&v));
}

TEST_F(VectorTest, FreeVector) {
    int x = 10;
    vector_add(&v,&x);
    vector_free(&v);

    EXPECT_EQ(vector_size(&v),(size_t)0);
    EXPECT_EQ(vector_capacity(&v),(size_t)0);
    EXPECT_EQ(v.ptr,(void*)NULL);
}

/* Swap Elements */
TEST_F(VectorTest, SwapElements) {
    int vals[] = {100,200,300};
    for (int i=0; i<3;i++) vector_add(&v,&vals[i]);

    // Swap index 0 and 2: Expected [300,200,100]
    vector_swap(&v,0,2);
    int retrieved;
    vector_get(&v,&retrieved,0); EXPECT_EQ(retrieved,300);
    vector_get(&v,&retrieved,2); EXPECT_EQ(retrieved,100);
}

/* Contains Operation */
static int compare_const_ints(const void* a, const void* b) {
    const int* ai = (const int*)a;
    const int* bi = (const int*)b;
    return (*ai > *bi) - (*ai < *bi);
}

TEST_F(VectorTest, ContainsValue) {
    int vals[] = {5,15,25,35};
    for (int i=0; i<4; i++) vector_add(&v,&vals[i]);

    int target = 25;
    EXPECT_EQ(vector_contains(&v, &target, compare_ints),1);

    int missing = 99;
    EXPECT_EQ(vector_contains(&v, &missing, compare_ints),0);
}

/* Sorting Tests */
TEST_F(VectorTest, SortAlreadySorted) {
    int vals[] = {1,2,3,4};
    for (int i=0; i<4; i++) vector_add(&v,&vals[i]);

    vector_sort(&v,compare_ints);
    for (int i=0; i<4; i++) {
        int retrieved;
        vector_get(&v,&retrieved,i);
        EXPECT_EQ(retrieved, vals[i]);
    }
}

TEST_F(VectorTest, SortReverseOrder) {
    int vals[] = {40,30,20,10};
    for (int i=0; i<4; i++) vector_add(&v,&vals[i]);

    vector_sort(&v,compare_ints);
    // After sort: [10,20,30,40]
    for (int i=0; i<4; i++) {
        int retrieved;
        vector_get(&v,&retrieved,i);
        EXPECT_EQ(retrieved,(i+1)*10);
    }
}

/* Extensive Growth Test */
TEST_F(VectorTest, LargeInsertionTest) {
    for (int i=0; i<1000; i++) {
        vector_add(&v,&i);
    }
    EXPECT_EQ(vector_size(&v),(size_t)1000);
    // Check a few random elements
    int val;
    vector_get(&v,&val,0);    EXPECT_EQ(val,0);
    vector_get(&v,&val,999);  EXPECT_EQ(val,999);
    vector_get(&v,&val,500);  EXPECT_EQ(val,500);
}

/* Test After Clear */
TEST_F(VectorTest, AfterClearAddElements) {
    int x = 1;
    vector_add(&v,&x);
    vector_add(&v,&x);
    vector_clear(&v);
    EXPECT_EQ(vector_size(&v),(size_t)0);
    EXPECT_TRUE(vector_empty(&v));

    int y = 7;
    vector_add(&v,&y);
    EXPECT_EQ(vector_size(&v),(size_t)1);

    int retrieved=0;
    vector_get(&v,&retrieved,0);
    EXPECT_EQ(retrieved,7);
}

/* Insert at the middle in a large vector */
TEST_F(VectorTest, InsertInLargeVector) {
    for(int i=0;i<10;i++) {
        vector_add(&v,&i);
    }
    int val = 999;
    vector_insert_element(&v,5,&val);
    // Expected: [0,1,2,3,4,999,5,6,7,8,9]
    EXPECT_EQ(vector_size(&v),(size_t)11);
    int retrieved;
    vector_get(&v,&retrieved,5);
    EXPECT_EQ(retrieved,999);
}

/* Contains with multiple elements the same */
TEST_F(VectorTest, ContainsMultipleSameValues) {
    int x=5;
    for(int i=0;i<10;i++) {
        vector_add(&v,&x);
    }
    // All are 5
    int searchVal=5;
    EXPECT_EQ(vector_contains(&v,&searchVal,compare_ints),1);

    int missing=10;
    EXPECT_EQ(vector_contains(&v,&missing,compare_ints),0);
}

/* Sort Random Data */
TEST_F(VectorTest, SortRandomData) {
    int data[] = {12, 4, 56, 2, 89, 10};
    for (int i=0;i<6;i++) vector_add(&v,&data[i]);

    vector_sort(&v,compare_ints);
    // After sort: [2,4,10,12,56,89]
    int sorted[] = {2,4,10,12,56,89};
    for (int i=0;i<6;i++){
        int retrieved;
        vector_get(&v,&retrieved,i);
        EXPECT_EQ(retrieved,sorted[i]);
    }
}

/* Check behavior of resize directly */
TEST_F(VectorTest, ManualResize) {
    int val=42;
    vector_add(&v,&val);
    vector_add(&v,&val);
    EXPECT_EQ(vector_capacity(&v),(size_t)4);

    vector_resize(&v,10);
    EXPECT_EQ(vector_capacity(&v),(size_t)10);
    EXPECT_EQ(vector_size(&v),(size_t)2);
}

/* Insert at front and end repeatedly */
TEST_F(VectorTest, InsertFrontAndEnd) {
    // Insert at front repeatedly
    for (int i=0;i<5;i++){
        vector_insert_element(&v,0,&i); // inserting at front
    }
    // Now vector should be [4,3,2,1,0]

    int retrieved=0;
    vector_get(&v,&retrieved,0);
    EXPECT_EQ(retrieved,4);

    vector_insert_element(&v, vector_size(&v), &retrieved); 
    // Insert at end with retrieved=4: [4,3,2,1,0,4]
    EXPECT_EQ(vector_size(&v),(size_t)6);
    vector_get(&v,&retrieved,5);
    EXPECT_EQ(retrieved,4);
}

/* Check that after free, we can re-init and use again */
TEST_F(VectorTest, ReInitAfterFree) {
    vector_free(&v);
    vector_init(&v,2,sizeof(int));
    EXPECT_EQ(vector_size(&v),(size_t)0);
    int x=123;
    vector_add(&v,&x);
    EXPECT_EQ(vector_size(&v),(size_t)1);

    int retrieved;
    vector_get(&v,&retrieved,0);
    EXPECT_EQ(retrieved,123);
}
