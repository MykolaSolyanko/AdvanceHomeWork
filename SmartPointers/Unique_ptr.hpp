
template <class T, typename Del = std::default_delete<T>> class Unique_ptr {
public:
  Unique_ptr() = default;
  Unique_ptr(T *ptr) : ptr_{ptr} {};
  Unique_ptr(const Unique_ptr &rhs) = delete;
  Unique_ptr(Unique_ptr &&rhs) : ptr_(rhs.ptr_) { rhs.ptr_ = nullptr; };
  ~Unique_ptr() { delete ptr_; };
  Unique_ptr &operator=(const Unique_ptr &rhs) = delete;
  Unique_ptr &operator=(Unique_ptr &&rhs) {
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
  };
  T &operator*() { return *ptr_; };
  T *operator->() { return ptr_; };
  T *release() {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  };
  void reset(T *ptr) {
    if (ptr == nullptr) {
      return;
    }
    del(ptr_);
    ptr_ = ptr = nullptr;
  };
  const T *get() const { return ptr_; };
  explicit operator bool() { return ptr_ == nullptr; };

private:
  T *ptr_{};
  Del del;
};

template <typename T, typename Del> class Unique_ptr<T[], Del> {
public:
  Unique_ptr() = default;
  Unique_ptr(T *ptr) : ptr_{ptr} {};
  Unique_ptr(const Unique_ptr &rhs) = delete;
  Unique_ptr(Unique_ptr &&rhs) : ptr_(rhs.ptr_) { rhs.ptr_ = nullptr; };
  ~Unique_ptr() { del(ptr_); };
  Unique_ptr &operator=(const Unique_ptr &rhs) = delete;
  Unique_ptr &operator=(Unique_ptr &&rhs) {
    del(ptr_);
    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    return *this;
  };
  T &operator*() { return *ptr_; };
  T *operator->() { return ptr_; };
  T *release() {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  };
  void reset(T *ptr) {
    if (ptr == nullptr) {
      return;
    }
    del(ptr_);
    ptr_ = ptr = nullptr;
  };
  const T *get() const { return ptr_; };
  explicit operator bool() { return ptr_ == nullptr; };
  T &operator[](size_t i) { return ptr_[i]; };

private:
  T *ptr_{};
  Del del;
};
