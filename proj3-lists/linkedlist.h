#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node *next;

    Node(T data) {
      this->data = data;
      this->next = nullptr;
    }

    Node(T data, Node *next) {
      this->data = data;
      this->next = next;
    }
  };

  size_t list_size;
  Node *list_front;

 public:
  /**
   * Default constructor. Creates an empty `LinkedList`.
   */
  LinkedList() {
    this->list_size = 0;
    this->list_front = nullptr;
  }

  /**
   * Returns whether the `LinkedList` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return this->list_size == 0;
  }

  /**
   * Returns the number of elements in the `LinkedList`.
   */
  size_t size() const {
    return this->list_size;
  }

  /**
   * Adds the given `T` to the front of the `LinkedList`.
   */
  void push_front(T data) {
    Node* newNode = new Node(data, list_front);
    this->list_front = newNode;
    this->list_size++;
  }

  /**
   * Adds the given `T` to the back of the `LinkedList`.
   */
  void push_back(T data) {
    Node* newNode = new Node(data, nullptr);

    if (this->size() == 0) {
      this->list_front = newNode;
    } else {
      Node* curr = this->list_front;
      while (curr->next != nullptr) {
        curr = curr->next;
      }
      curr->next = newNode;
    }

    this->list_size++;
  }

  /**
   * Removes the element at the front of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (this->empty()) {
      throw out_of_range("pop_front() called on empty list.");
    }

    Node* oldFront = this->list_front;
    T oldData = oldFront->data;

    this->list_front = oldFront->next;
    delete oldFront;
    this->list_size--;
    
    return oldData;
  }

  /**
   * Removes the element at the back of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (this->empty()) {
      throw out_of_range("pop_back() called on empty list.");
    }

    Node* curr = this->list_front;
    Node* prev = nullptr;

    while (curr->next != nullptr) {
      prev = curr;
      curr = curr->next;
    }

    T oldData = curr->data;

    if (prev) {
      prev->next = nullptr;
    } else {
      this->list_front = nullptr;
    }

    delete curr;
    this->list_size--;

    return oldData;
  }

  /**
   * Empties the `LinkedList`, releasing all allocated memory, and resetting
   * member variables appropriately.
   */
  void clear() {
    Node* curr = this->list_front;

    while (curr != nullptr) {
      Node* next = curr->next;
      delete curr;
      curr = next;
    }

    this->list_front = nullptr;
    this->list_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~LinkedList() {
    this->clear();
  }

  /**
   * Returns the element at the given index in the `LinkedList`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index >= this->size() || index < 0) {
      throw out_of_range("at() invalid index access attempt");
    }

    int i = 0;
    Node* curr = this->list_front;
    while (i < index) {
      curr = curr->next;
      i++;
    }

    return curr->data;
  }

  /**
   * Copy constructor. Creates a deep copy of the given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList(const LinkedList &other) {
    this->list_front = nullptr;

    if (other.empty()) {
      return;
    }
    
    Node* curr = other.list_front;
    Node* prev = nullptr;

    while (curr != nullptr) {
      Node* newCurr = new Node(curr->data);

      if (prev == nullptr) {
        this->list_front = newCurr;
      } else {
        prev->next = newCurr;
      }

      prev = newCurr;
      curr = curr->next;
      this->list_size++;
      
    } 
  }

  /**
   * Assignment operator. Sets the current `LinkedList` to a deep copy of the
   * given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList &operator=(const LinkedList &other) {
    if (this == &other) {
      return *this;
    }

    this->clear();

    if (other.empty()) {
      return *this;
    }

    Node* curr = other.list_front;
    Node* prev = nullptr;

    while (curr != nullptr) {
      Node* newCurr = new Node(curr->data);

      if (prev == nullptr) {
        this->list_front = newCurr;
      } else {
        prev->next = newCurr;
      }

      prev = newCurr;
      curr = curr->next;
      this->list_size++;
      
    } 

    return *this;
  }

  /**
   * Converts the `LinkedList` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    string result = "[";
    
    Node* curr = this->list_front;

    while (curr != nullptr) {
      result += std::to_string(curr->data);
      if (curr->next != nullptr) {
        result += ", ";
      }
      curr = curr->next;
    }

    result += "]";
    return result;
  }

  /**
   * Searches the `LinkedList` for the first matching element, and returns its
   * index. If no match is found, returns "-1".
   */
  int find(const T &data) {
    int index = 0;

    Node* curr = this->list_front;

    while (curr != nullptr) {
      if (curr->data == data) {
        return index;
      }

      curr = curr->next;
      index++;
    }

    return -1;
  }

  /**
   * Remove the element at the specified index in this list.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  void remove_at(size_t index) {
    if (index >= this->size()) {
      throw out_of_range("remove_at() accesses invalid index");
    }

    Node* curr = this->list_front;
    Node* prev = nullptr;

    if (index == 0) {
      this->list_front = curr->next;
      delete curr;
      return;
    }

    for (int i = 0; i < index; i++) {
      prev = curr;
      curr = curr->next;
    }

    prev->next = curr->next;
    delete curr;
  }

  /**
   * Inserts the given `T` as a new element in the `LinkedList` after
   * the given index. If the index is invalid, throws `out_of_range`.
   */
  void insert_after(size_t index, T data) {
    if (index >= this->size()) {
      throw out_of_range("insert_after() accesses invalid index");
    }

    Node* curr = this->list_front;

    for (int i = 0; i < index; i++) {
      curr = curr->next;
    }

    Node* newNode = new Node(data);
    newNode->next = curr->next;
    curr->next = newNode;
    this->list_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `LinkedList`, starting at index 1. Must run in O(N).
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    if (this->size() == 0 || this->size() == 1) {
      return;
    }
    
    Node* curr = this->list_front;
    Node* del = nullptr;

    while (curr != nullptr && curr->next != nullptr) {
      del = curr->next;
      curr->next = del->next;
      delete del;
      curr = curr->next;
      this->list_size--;
    }
  }

  /**
   * Returns a pointer to the node at the front of the `LinkedList`. For
   * autograder testing purposes only.
   */
  void *front() const {
    return this->list_front;
  }
};