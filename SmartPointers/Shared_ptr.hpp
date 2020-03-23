#include <memory>

template <class T, typename Del = std::default_delete<T>> class Shared_ptr {
public:
  Shared_ptr() = default;
  Shared_ptr(T *ptr) : ptr_{ptr}, count_(new size_t(1)){};
  Shared_ptr(Shared_ptr &rhs) : ptr_(rhs.ptr_), count_(rhs.count_) {
    ++(*count_);
  };
  Shared_ptr(Shared_ptr &&rhs) : ptr_(rhs.ptr_), count_(rhs.count_) {
    rhs.ptr_ = nullptr;
    rhs.count_ = 0;
  };
  ~Shared_ptr() { count_delitor(); }
  Shared_ptr &operator=(const Shared_ptr &rhs) {
    if (this == &rhs) {
      return *this;
    }
    count_delitor();
    ptr_ = rhs.ptr_;
    count_ = rhs.count_;
    (*count_)++;
  };
  Shared_ptr &operator=(Shared_ptr &&rhs) {
    ptr_ = rhs.ptr_;
    count_ = rhs.count_;
    rhs.ptr_ = nullptr;
    rhs.count_ = 0;
    return *this;
  };

  void reset(){

  };
  void reset(T *ptr) {
    if (ptr == nullptr) {
      return;
    }
    if (*count_ == 1) {
      del(ptr_);
      ptr_ = ptr;
    } else if (*count_ > 1) {
      ptr_ = ptr;
    }
  };
  void reset(T *ptr, Del Deleter) {
    if (ptr == nullptr) {
      return;
    }
    if (*count_ == 1) {
      Deleter(ptr_);
      ptr_ = ptr;
    } else if (*count_ > 1) {
      ptr_ = ptr;
    }
  };
  const T *get() const { return ptr_; };
  size_t use_count() { return (count_) ? *count_ : 0; };

  explicit operator bool() { return ptr_ == nullptr; };
  bool unique() const { return (*count_ == 1); }
  T &operator*() { return *ptr_; };
  T *operator->() { return ptr_; };

private:
  void count_delitor() {
    if (count_) {
      if (*count_ == 1) {
        count_ = 0;
        del(ptr_);
      } else {
        --(*count_);
      }
    }
  }
  T *ptr_{};
  Del del;
  size_t *count_{};
};

template <class T, typename Del> class Shared_ptr<T[], Del> {
public:
  Shared_ptr() = default;
  Shared_ptr(T *ptr) : ptr_{ptr}, count_(new size_t(1)){};
  Shared_ptr(Shared_ptr &rhs) : ptr_(rhs.ptr_), count_(rhs.count_) {
    ++(*count_);
  };
  Shared_ptr(Shared_ptr &&rhs) : ptr_(rhs.ptr_), count_(rhs.count_) {
    rhs.ptr_ = nullptr;
    rhs.count_ = 0;
  };
  ~Shared_ptr() { count_delitor(); }
  Shared_ptr &operator=(const Shared_ptr &rhs) {
    if (this == &rhs) {
      return *this;
    }
    count_delitor();
    ptr_ = rhs.ptr_;
    count_ = rhs.count_;
    (*count_)++;
  };
  Shared_ptr &operator=(Shared_ptr &&rhs) {
    ptr_ = rhs.ptr_;
    count_ = rhs.count_;
    rhs.ptr_ = nullptr;
    rhs.count_ = 0;
    return *this;
  };

  void reset(){

  };
  void reset(T *ptr) {
    if (ptr == nullptr) {
      return;
    }
    if (*count_ == 1) {
      // delete[] prt_;
      Del(ptr_);
      ptr_ = ptr;
    } else if (*count_ > 1) {
      ptr_ = ptr;
    }
  };
  void reset(T *ptr, Del Deleter) {
    if (ptr == nullptr) {
      return;
    }
    if (*count_ == 1) {
      Deleter(ptr_);
      ptr_ = ptr;
    } else if (*count_ > 1) {
      ptr_ = ptr;
    }
  };
  const T *get() const { return ptr_; };
  size_t use_count() { return (count_) ? *count_ : 0; };

  explicit operator bool() { return ptr_ == nullptr; };
  bool unique() const { return (*count_ == 1); }
  T &operator*() { return *ptr_; };
  T *operator->() { return ptr_; };
  T &operator[](size_t i) { return ptr_[i]; };

private:
  void count_delitor() {
    if (count_) {
      if (*count_ == 1) {
        count_ = 0;
        // delete[] ptr_;
        del(ptr_);
      } else {
        --(*count_);
      }
    }
  }
  T *ptr_{};
  Del del;
  size_t *count_{};
};
