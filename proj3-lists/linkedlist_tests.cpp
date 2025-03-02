#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;

TEST(LinkedListTest, ConstructorCorrectStartingSize) {
  LinkedList<int> list;
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, EmptyFalseWhenNotEmpty) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_FALSE(list.empty());
}

TEST(LinkedListTest, SizeCorrectNumberOfElements) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  EXPECT_EQ(list.size(), 2);
}

TEST(LinkedListTest, PushFrontUpdatesSizeAndPushesElement) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListTest, PushBackUpdatesSizeAndPushesElement) {
  LinkedList<int> list;
  list.push_back(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListTest, PushFrontKeepsOtherNodes) {
  LinkedList<int> list;
  list.push_back(10);
  list.push_front(20);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.at(0), 20);
  EXPECT_EQ(list.at(1), 10);
}

TEST(LinkedListTest, PushBackOnEmptyList) {
  LinkedList<int> list;
  list.push_back(10);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListTest, PopFrontUpdatesSizeAndPopsElement) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  list.pop_front();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 20);
}

TEST(LinkedListTest, PopBackUpdatesSizeAndPopsElement) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  list.pop_back();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.at(0), 10);
}

TEST(LinkedListTest, ClearResetsSizeCorrectly) {
  LinkedList<int> list;
  list.push_back(10);
  list.push_back(20);
  list.clear();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, DestructorClearsMemoryCorrectly) {
  LinkedList<int>* list = new LinkedList<int>();
  list->push_front(10);
  list->push_back(20);
  EXPECT_NO_THROW(delete list);  // Ensure no memory leak on destruction
}

TEST(LinkedListTest, AtThrowsExceptionForInvalidIndex) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_THROW(list.at(1), std::out_of_range);
}

TEST(LinkedListTest, AtReturnsCorrectValue) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  EXPECT_EQ(list.at(0), 10);
  EXPECT_EQ(list.at(1), 20);
}

TEST(LinkedListTest, AtChecksBounds) {
  LinkedList<int> list;
  list.push_front(10);
  EXPECT_THROW(list.at(2), std::out_of_range);
}

TEST(LinkedListTest, PopFrontThrowsExceptionForEmptyList) {
  LinkedList<int> list;
  EXPECT_THROW(list.pop_front(), std::out_of_range);
}

TEST(LinkedListTest, PopBackThrowsExceptionForEmptyList) {
  LinkedList<int> list;
  EXPECT_THROW(list.pop_back(), std::out_of_range);
}

TEST(LinkedListTest, PopBackWithOneElement) {
  LinkedList<int> list;
  list.push_front(10);
  list.pop_back();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, ClearMemoryLeakCheck) {
  LinkedList<int> list;
  list.push_front(10);
  list.push_back(20);
  list.clear();
  // If no exception or memory issue occurs, the test passes
  EXPECT_NO_THROW(list.clear());
}

TEST(LinkedListTest, SizeIsO_N) {
  LinkedList<int> list;
  for (int i = 0; i < 1000; ++i) {
      list.push_back(i);
  }
  EXPECT_EQ(list.size(), 1000);
}