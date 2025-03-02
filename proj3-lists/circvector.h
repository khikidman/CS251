#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class CircVector {
 private:
  T *data;
  size_t vec_size;
  size_t capacity;
  size_t front_idx;

  // TODO_STUDENT: add private helper functions, such as resize
  // You may also find a "wrapping" function helpful.
  void resize() {
    size_t new_capacity = this->capacity * 2;
    T* new_data = new T[new_capacity];

    for (size_t i = 0; i < vec_size; i++) {
        new_data[i] = this->data[(this->front_idx + i) % this->capacity];
    }

    delete[] this->data;
    this->data = new_data;
    this->capacity = new_capacity;
    this->front_idx = 0;
  }

 public:
  /**
   * Default constructor. Creates an empty `CircVector` with capacity 10.
   */
  CircVector() {
    this->data = new T[10];
    this->vec_size = 0;
    this->capacity = 10;
    this->front_idx = 0;
  }

  /**
   * Creates an empty `CircVector` with given capacity. Capacity must exceed 0.
   */
  CircVector(size_t capacity) {
    if (capacity <= 0) {
      throw invalid_argument("Capacity must exceed 0.");
    }
    this->data = new T[capacity];
    this->vec_size = 0;
    this->capacity = capacity;
    this->front_idx = 0;
  }

  /**
   * Returns whether the `CircVector` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return this->vec_size == 0;
  }

  /**
   * Returns the number of elements in the `CircVector`.
   */
  size_t size() const {
    return this->vec_size;
  }

  /**
   * Adds the given `T` to the front of the `CircVector`.
   */
  void push_front(T elem) {
    if (this->vec_size == this->capacity) {
      resize();
    }

    if (this->front_idx == 0) {
      this->front_idx = capacity - 1;
    } else {
      this->front_idx = front_idx - 1;
    }

    this->data[front_idx] = elem;
    this->vec_size++;
  }

  /**
   * Adds the given `T` to the back of the `CircVector`.
   */
  void push_back(T elem) {
    if (this->data == nullptr) {
      this->data = new T[this->capacity];
    }
    if (this->vec_size == this->capacity) {
      resize();
    }
    size_t back_idx = (this->front_idx + this->vec_size) % this->capacity;
    this->data[back_idx] = elem;
    this->vec_size++;
  }

  /**
   * Removes the element at the front of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (this->empty()) {
      throw out_of_range("pop_front() called on empty CircVector");
    }
    T front_elem = this->data[this->front_idx];
    this->front_idx = (this->front_idx + 1) % this->capacity;
    this->vec_size--;
    return front_elem;
  }

  /**
   * Removes the element at the back of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (this->empty()) {
      throw out_of_range("pop_back() called on empty CircVector");
    }
    size_t back_idx = (this->front_idx + this->vec_size - 1) % capacity;
    T back_elem = this->data[back_idx];
    this->vec_size--;
    return back_elem;
  }

  /**
   * Removes all elements from the `CircVector`.
   */
  void clear() {
    if (this->data != nullptr) {
      delete[] this->data;
      this->data = nullptr;
    }
    vec_size = 0;
    front_idx = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~CircVector() {
    this->clear();
  }

  /**
   * Returns the element at the given index in the `CircVector`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index >= this->vec_size) {
      throw out_of_range("Index out of range");
    }
    return this->data[(this->front_idx + index) % this->capacity];
  }

  /**
   * Copy constructor. Creates a deep copy of the given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector(const CircVector &other) {
    this->vec_size = other.vec_size;
    this->capacity = other.capacity;
    this->front_idx = other.front_idx;
    this->data = new T[other.capacity];
    for (int i = 0; i < other.vec_size; i++) {
      this->data[(this->front_idx + i) % this->capacity] = other.data[(other.front_idx + i) % other.capacity];
    }
  }

  /**
   * Assignment operator. Sets the current `CircVector` to a deep copy of the
   * given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector &operator=(const CircVector &other) {
    if (this == &other) {
      return *this;
    }
    
    this->clear();

    this->vec_size = other.vec_size;
    this->capacity = other.capacity;
    this->front_idx = other.front_idx;
    this->data = new T[other.capacity];
    for (int i = 0; i < other.vec_size; i++) {
      this->data[(this->front_idx + i) % this->capacity] = other.data[(other.front_idx + i) % other.capacity];
    }
    return *this;
  }

  /**
   * Converts the `CircVector` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    string result = "[";
    for (int i = 0; i < this->vec_size; i++) {
      result += std::to_string(this->data[(this->front_idx + i) % capacity]);
      if (i < this->vec_size - 1) {
        result += ", ";
      }
    }
    result += "]";
    return result;
  }

  /**
   * Searches the `CircVector` for the first matching element, and returns its
   * index in the `CircVector`. If no match is found, returns "-1".
   */
  int find(const T &target) {
    for (int i = 0; i < this->vec_size; i++) {
      if (this->data[(this->front_idx + i) % capacity] == target) {
        return i;
      }
    }
    return -1;
  }

  /**
   * Remove the element at the specified index in this list.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  void remove_at(size_t index) {
    if (index >= this->vec_size) {
      throw out_of_range("remove_at index out of range");
    }

    for (int i = index; i < this->vec_size - 1; i++) {
      this->data[(this->front_idx + i) % capacity] = this->data[(front_idx + i + 1) % capacity];
    }

    this->vec_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `CircVector` after
   * the given index. If the index is invalid, throws `out_of_range`.
   */
  void insert_after(size_t index, T elem) {
    if (index >= this->vec_size) {
      throw out_of_range("insert_after index out of range");
    }

    if (this->vec_size == this->capacity) {
      this->resize();
    }

    for (int i = this->vec_size; i > index + 1; i--) {
      this->data[(this->front_idx + i) % this->capacity] = this->data[(front_idx + i - 1) % capacity];
    }

    this->data[(this->front_idx + index + 1) % this->capacity] = elem;
    this->vec_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `CircVector`, starting at index 1. Must run in O(N). May not reallocate.
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    int i = 1;
    while (i < this->vec_size) {
      remove_at(i);
      i++;
    }
  }

  /**
   * Returns a pointer to the underlying memory managed by the `CircVec`.
   * For autograder testing purposes only.
   */
  T *get_data() const {
    return this->data;
  }

  /**
   * Returns the capacity of the underlying memory managed by the `CircVec`. For
   * autograder testing purposes only.
   */
  size_t get_capacity() const {
    return this->capacity;
  }
};