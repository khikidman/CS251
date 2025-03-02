#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;

TEST(LinkedListCore, ConstructorCorrectStartingSize) {
  LinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListCore, EmptyFalseWhenNotEmpty) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_FALSE(list.empty());
}

TEST(LinkedListCore, SizeCorrectNumberOfElements) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  EXPECT_EQ(list.size(), 2);
}

TEST(LinkedListCore, PushFrontUpdatesSizeAndPushesElement) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListCore, PushBackUpdatesSizeAndPushesElement) {
  LinkedList<int> list;
  list.push_back(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListCore, PushFrontKeepsOtherNodes) {
  LinkedList<int> list;
  list.push_back(10);
  list.push_front(20);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.at(0), 20);
  EXPECT_EQ(list.at(1), 10);
}

TEST(LinkedListCore, PushBackOnEmptyList) {
  LinkedList<int> list;
  list.push_back(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListCore, PopFrontUpdatesSizeAndPopsElement) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  list.pop_front();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 20);
}

TEST(LinkedListCore, PopBackUpdatesSizeAndPopsElement) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  list.pop_back();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListCore, ClearResetsSizeCorrectly) {
  LinkedList<int> list;
  list.push_back(10);
  list.push_back(20);
  list.clear();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListCore, DestructorClearsMemoryCorrectly) {
  LinkedList<int>* list = new LinkedList<int>();
  list->push_front(10);
  list->push_back(20);
  EXPECT_NO_THROW(delete list);
}

TEST(LinkedListCore, AtThrowsExceptionForInvalidIndex) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_THROW(list.at(1), std::out_of_range);
}

TEST(LinkedListCore, AtReturnsCorrectValue) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  EXPECT_EQ(list.at(0), 10);
  EXPECT_EQ(list.at(1), 20);
}

TEST(LinkedListCore, AtChecksBounds) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_THROW(list.at(2), std::out_of_range);
}

TEST(LinkedListCore, PopFrontThrowsExceptionForEmptyList) {
  LinkedList<int> list;
  EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(LinkedListCore, PopBackThrowsExceptionForEmptyList) {
  LinkedList<int> list;
  EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TEST(LinkedListCore, PopBackWithOneElement) {
  LinkedList<int> list;
  list.push_front(10);
  list.pop_back();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListCore, ClearMemoryLeakCheck) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  list.clear();
  EXPECT_NO_THROW(list.clear());
}

TEST(LinkedListCore, SizeIsO_N) {
  LinkedList<int> list;
  for (int i = 0; i < 1000; ++i) {
      list.push_back(i);
  }
  EXPECT_EQ(list.size(), 1000);
}

// Augmented tests

TEST(LinkedListAugmented, CopyConstructorCreatesEmptyListWhenEmpty) {
  LinkedList<int> original;
  LinkedList<int> copy(original);
  EXPECT_TRUE(copy.empty());
}

TEST(LinkedListAugmented, CopyConstructorCopiesAllElements) {
  LinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);
  LinkedList<int> copy(original);
  EXPECT_EQ(copy.size(), 3);
  EXPECT_EQ(copy.at(0), 1);
  EXPECT_EQ(copy.at(2), 3);
}

TEST(LinkedListAugmented, CopyConstructorNonEmptyList) {
  LinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  LinkedList<int> copy(original);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(0), 1);
  EXPECT_EQ(copy.at(1), 2);
}

TEST(LinkedListAugmented, CopyConstructorCopyingSomeElements) {
  LinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  LinkedList<int> copy(original);
  original.push_back(3);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(1), 2);
}

TEST(LinkedListAugmented, CopyConstructorWorksOnEmptyList) {
  LinkedList<int> original;
  LinkedList<int> copy(original);
  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(copy.size(), 0);
}

TEST(LinkedListAugmented, AssignmentOperatorHandlesSelfAssignment) {
  LinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  LinkedList<int> copy;
  copy = original;
  LinkedList<int> copy2;
  copy2 = copy;
  copy = copy2;
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(0), 1);
  EXPECT_EQ(copy.at(1), 2);
}

TEST(LinkedListAugmented, AssignmentOperatorWithChangesToOriginalAfterAssignment) {
  LinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  LinkedList<int> copy;
  copy = original;
  original.push_back(3);
  EXPECT_EQ(copy.size(), 2);
  EXPECT_EQ(copy.at(1), 2);
}

TEST(LinkedListAugmented, AssignmentOperatorAssignedEmpty) {
  LinkedList<int> original;
  original.push_back(1);
  original.push_back(2);
  LinkedList<int> copy;
  copy = original;
  copy = LinkedList<int>();
  EXPECT_TRUE(copy.empty());
}

TEST(LinkedListAugmented, ToStringCorrectness) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list.to_string(), "[1, 2, 3]");
}

TEST(LinkedListAugmented, ToStringHandlesEmptyList) {
  LinkedList<int> list;
  EXPECT_EQ(list.to_string(), "[]");
}

TEST(LinkedListAugmented, FindReturnsCorrectIndex) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list.find(2), 1);
}

TEST(LinkedListAugmented, FindElementNotFound) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  EXPECT_EQ(list.find(5), -1);
}

// Extras tests

TEST(LinkedListExtras, InsertAfterUpdatesSizeAndInsertsElement) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.insert_after(1, 3);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.at(2), 3);
}

TEST(LinkedListExtras, InsertAfterHandlesIndex0) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.insert_after(0, 3);
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.at(1), 3);
}

TEST(LinkedListExtras, InsertAfterUpdatesSize) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.insert_after(1, 3);
  EXPECT_EQ(list.size(), 3);
}

TEST(LinkedListExtras, InsertAfterThrowsExceptionOnInvalidIndex) {
  LinkedList<int> list;
  list.push_back(1);
  EXPECT_THROW(list.insert_after(10, 2), std::out_of_range);
}

TEST(LinkedListExtras, RemoveEveryOtherRemovesCorrectElements) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  list.remove_every_other();
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.at(0), 1);
  EXPECT_EQ(list.at(1), 3);
  EXPECT_EQ(list.at(2), 5);
}

TEST(LinkedListExtras, RemoveEveryOtherHandlesEmptyList) {
  LinkedList<int> list;
  EXPECT_NO_THROW(list.remove_every_other());
  EXPECT_EQ(list.size(), 0);
}

TEST(LinkedListExtras, RemoveEveryOtherWorksWithOddSize) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);
  list.push_back(5);
  list.remove_every_other();
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.at(0), 1);
  EXPECT_EQ(list.at(1), 3);
  EXPECT_EQ(list.at(2), 5);
}

TEST(LinkedListExtras, RemoveEveryOtherUpdatesSize) {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.remove_every_other();
  EXPECT_EQ(list.size(), 1);
}
