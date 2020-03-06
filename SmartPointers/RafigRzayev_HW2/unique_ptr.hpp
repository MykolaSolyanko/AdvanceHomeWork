#pragma once

#include <iostream>

// Variadic template to enable different template arg number
template <typename...> class unique_ptr;

// General template
// Destructor calls "delete"
template <typename T> class unique_ptr<T> {
public:
  unique_ptr() = default;
  unique_ptr(T *ptr) noexcept : ptr_{ptr} {}
  unique_ptr(unique_ptr &&rhs) noexcept : ptr_{rhs.ptr_} { rhs.ptr_ = nullptr; }
  unique_ptr &operator=(unique_ptr &&rhs) noexcept {
    delete ptr_;
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    return *this;
  }
  ~unique_ptr() noexcept { delete ptr_; }

  T *get() noexcept { return ptr_; }

  void reset(T *ptr = nullptr) noexcept {
    delete ptr_;
    ptr_ = ptr;
  }

  T *release() noexcept {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  T *operator->() { return ptr_; }
  T &operator*() { return *ptr_; }

private:
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

  T *ptr_{nullptr};
};

// Array template
// Destructor calls "delete[]"
// [] operator added to access array elements
template <typename T> class unique_ptr<T[]> {
public:
  unique_ptr() = default;
  unique_ptr(T *ptr) noexcept : ptr_{ptr} {}
  unique_ptr(unique_ptr &&rhs) noexcept : ptr_{rhs.ptr_} { rhs.ptr_ = nullptr; }
  unique_ptr &operator=(unique_ptr &&rhs) noexcept {
    delete[] ptr_;
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    return *this;
  }
  ~unique_ptr() noexcept { delete[] ptr_; }

  T *get() noexcept { return ptr_; }

  void reset(T *ptr = nullptr) noexcept {
    delete[] ptr_;
    ptr_ = ptr;
  }

  T *release() noexcept {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  T *operator->() { return ptr_; }
  T &operator*() { return *ptr_; }
  T &operator[](size_t i) { return *(ptr_ + i); }

private:
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

  T *ptr_{nullptr};
};

// Template for user-defined destructor
template <typename T, typename D> class unique_ptr<T, D> {
public:
  unique_ptr() = default;
  unique_ptr(T *ptr, D dtor) : ptr_{ptr}, dtor_{dtor} {}
  unique_ptr(unique_ptr &&rhs) : ptr_{rhs.ptr_}, dtor_{rhs.dtor_} {
    rhs.ptr_ = nullptr;
  }
  unique_ptr &operator=(unique_ptr &&rhs) {
    dtor_(ptr_);
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    return *this;
  }
  ~unique_ptr() { dtor_(ptr_); }

  T *get() noexcept { return ptr_; }

  void reset(T *ptr = nullptr) {
    dtor_(ptr_);
    ptr_ = ptr;
  }

  T *release() noexcept {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  T *operator->() { return ptr_; }
  T &operator*() { return *ptr_; }

private:
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

  T *ptr_{nullptr};
  D *dtor_{nullptr};
};
