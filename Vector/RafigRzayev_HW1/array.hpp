// DUMMY CLASS FOR TESTING VECTOR

#pragma once
#include <iostream>
class Array {
public:
Array(){
    std::cout << "Array Default Constructor\n";
}
Array(size_t size) : size_{size}{
    data_ = new int[size_]{};
    std::cout << "Array User Constructor\n";
}
Array(const Array&rhs) : size_{rhs.size_} {
    if(size_ == 0) {
        return;
    }
    data_ = new int[size_]{};
    std::cout << "Array Copy Constructor\n";
}
Array& operator=(const Array& rhs) {
    std::cout << "Array Copy Assignment\n";
    if(this == &rhs) {
        return *this;
    }
    delete data_;
    size_ = rhs.size_;
    data_ = new int[size_]{};
    return *this;
}
Array(Array&&rhs) : data_{rhs.data_}, size_{rhs.size_} {
    std::cout << "Array Move Constructor\n";
    rhs.size_ = 0;
    rhs.data_ = nullptr;
}
Array& operator=(Array&&rhs) noexcept {
    std::cout << "Array Move Assignment\n";
    delete data_;
    data_ = rhs.data_;
    size_ = rhs.size_;
    rhs.size_ = 0;
    rhs.data_ = nullptr;
    return *this;
}

~Array() {
    delete [] data_;
    std::cout << "Array Destructor\n";
}
void print(const char* c) const {
    std::cout << c << " -> ";
    if(size_ == 0) {
        std::cout << "Empty\n";
        return;
    }
    std::cout << "[";
    for(size_t i{0}; i < size_; ++i) {
        std::cout << data_[i] << " ";
    }
    std::cout << "]" << std::endl;
}

private:
int* data_{nullptr};
size_t size_{0};
};