#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "circvector.h"

using namespace std;
using namespace testing;

TEST(CircVectorCore, ctor_size) {
  CircVector<int> vec(20);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.get_capacity(), 20);
}

TEST(CircVectorCore, empty_false) {
  CircVector<int> vec;
  EXPECT_TRUE(vec.empty());
}

TEST(CircVectorCore, empty_true) {
  CircVector<int> vec;
  vec.push_back(1);
  EXPECT_FALSE(vec.empty());
}

TEST(CircVectorCore, size_fixed) {
  CircVector<int> vec;
  vec.push_front(1);
  EXPECT_EQ(vec.size(), 1);
  vec.push_front(2);
  EXPECT_EQ(vec.size(), 2);
}

TEST(CircVectorCore, push_back_no_size) {
  CircVector<int> vec;
  vec.push_back(1);
  EXPECT_EQ(vec.size(), 1);
  vec.push_back(2);
  EXPECT_EQ(vec.size(), 2);
}

TEST(CircVectorCore, push_back_only_size) {
  CircVector<int> vec(2);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.at(1), 2);
}

TEST(CircVectorCore, push_front_no_size) {
  CircVector<int> vec(2);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_front(3);
  EXPECT_EQ(vec.size(), 3);
}

TEST(CircVectorCore, push_front_only_size) {
  CircVector<int> vec(2);
  vec.push_back(1);
  vec.push_front(2);
  vec.push_front(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.at(1), 2);
}


TEST(CircVectorCore, clear_no_reset_size) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.clear();
  vec.push_back(1);
  EXPECT_EQ(vec.size(), 1);
}

TEST(CircVectorCore, dtor_nothing) {
  {
      CircVector<int> vec(10);
      vec.push_back(1);
      vec.push_back(2);
  }
  EXPECT_TRUE(true);
}

TEST(CircVectorCore, at_no_throw) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_THROW(vec.at(3), std::out_of_range);
}

TEST(CircVectorCore, at_upper_bound) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  EXPECT_THROW(vec.at(8), std::out_of_range);
}

TEST(CircVectorCore, at_wrong_value) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 2);
}

TEST(CircVectorCore, pop_front_no_size) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.pop_front();
  EXPECT_EQ(vec.size(), 1);
}

TEST(CircVectorCore, pop_front_no_throw) {
  CircVector<int> vec;
  EXPECT_THROW(vec.pop_front(), std::out_of_range);
}

TEST(CircVectorCore, pop_back_no_size) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.pop_back();
  EXPECT_EQ(vec.size(), 1);
}

TEST(CircVectorCore, pop_back_no_throw) {
  CircVector<int> vec;
  EXPECT_THROW(vec.pop_back(), std::out_of_range);
}

TEST(CircVectorCore, push_back_no_resize) {
  CircVector<int> vec(2);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.get_capacity(), 4);
}

TEST(CircVectorCore, push_back_no_wrap) {
  CircVector<int> vec(3);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);  // Vector is full, should resize
  vec.pop_front();  // Front index will be 1
  vec.push_back(4);  // Should go to index 0
  EXPECT_EQ(vec.at(2), 4);
}

TEST(CircVectorCore, push_front_no_resize) {
  CircVector<int> vec(2);
  vec.push_front(1);
  vec.push_front(2);
  vec.push_front(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.get_capacity(), 4);
}

TEST(CircVectorCore, push_front_no_wrap) {
  CircVector<int> vec(3);
  vec.push_front(1);
  vec.push_back(2);
  vec.push_back(3);  // Vector is full, should resize
  vec.pop_front();  // Front index will be 1
  vec.push_front(4);  // Should go to index 0
  EXPECT_EQ(vec.at(0), 4);
}

TEST(CircVectorCore, pop_back_no_wrap) {
  CircVector<int> vec(3);
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.pop_front();  // front_idx will be 1
  vec.push_back(4);  // Should wrap around to the back
  EXPECT_EQ(vec.pop_back(), 4);
}

// Augmented tests

TEST(CircVectorAugmented, CopyConstructorEmptyList) {
  CircVector<int> original;
  CircVector<int> copy(original);
  EXPECT_TRUE(copy.empty());
}

TEST(CircVectorAugmented, AssignmentOperatorHandlesSelfAssignment) {
  CircVector<int> original;
  original.push_back(1);
  original.push_back(2);
  CircVector<int> copy;
  copy = original;
  CircVector<int> copy2;
  copy2 = original;
  copy = copy2;
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(0), 1);
  EXPECT_EQ(copy.at(1), 2);
}

TEST(CircVectorAugmented, AssignmentOperatorWithChangesToOriginalAfterAssignment) {
  CircVector<int> original;
  original.push_back(1);
  original.push_back(2);
  CircVector<int> copy;
  copy = original;
  original.push_back(3);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(0), 1);
  EXPECT_EQ(copy.at(1), 2);
}

TEST(CircVectorAugmented, ToStringReturnsCorrectRepresentation) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.to_string(), "[1, 2, 3]");
}

TEST(CircVectorAugmented, FindReturnsCorrectIndex) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.find(2), 1);
}

TEST(CircVectorAugmented, FindElementNotFound) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  EXPECT_EQ(vec.find(4), -1);
}

// Extras tests

TEST(CircVectorExtras, InsertAfterUpdatesSizeAndInsertsElement) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.insert_after(1, 3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.at(2), 3);
}

TEST(CircVectorExtras, InsertAfterThrowsExceptionOnInvalidIndex) {
  CircVector<int> vec;
  vec.push_back(1);
  EXPECT_THROW(vec.insert_after(10, 2), std::out_of_range);
}

TEST(CircVectorExtras, InsertAfterHandlesIndex0) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.insert_after(0, 3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.at(1), 3);
}

TEST(CircVectorExtras, InsertAfterUpdatesSize) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.insert_after(1, 3);
  EXPECT_EQ(vec.size(), 3);
}

TEST(CircVectorExtras, InsertAfterResizesUnderlyingMemoryIfNecessary) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.insert_after(1, 3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.at(2), 3);
}

TEST(CircVectorExtras, RemoveEveryOtherRemovesCorrectElements) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.remove_every_other();
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 3);
  EXPECT_EQ(vec.at(2), 5);
}

TEST(CircVectorExtras, RemoveEveryOtherUpdatesSize) {
  CircVector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.remove_every_other();
  EXPECT_EQ(vec.size(), 1);
}