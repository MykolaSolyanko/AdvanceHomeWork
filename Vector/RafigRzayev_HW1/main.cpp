#include "vector.hpp"
#include <iostream>

template <typename T1>
void print(Vector<T1>&vec) {
    std::cout << "SIZE: " << vec.size() << "  CAPACITY: " << vec.capacity() << "\nDATA: \n";
    for(auto &i : vec) {
        std::cout << i << std::endl;
    }
}

int main() {  
    Vector <int> v;
    v.emplace_back(1);
    print(v);
    return 0;
}