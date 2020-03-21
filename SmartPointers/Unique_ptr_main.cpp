#include "Unique_ptr.hpp"
#include <cstdio>
#include <iostream>

class debug {
public:
  ~debug() { std::cout << "~debug()" << std::endl; }
};

int main() {

  Unique_ptr<int> ptr1{new int{8}};
  Unique_ptr<int> ptr_copy{std::move(ptr1)};
  Unique_ptr<int> ptr2{new int{7}};
  std::cout << "Get ptr1 = " << *ptr_copy.get() << std::endl;
  std::cout << "Get ptr2 = " << *ptr2.get() << std::endl;
  if (ptr_copy.get() == nullptr) {
    std::cout << "ptr1 = nullptr";
  } else {
    std::cout << "ptr1 not have nullptr";
  }
  Unique_ptr<int[]> arr_ptr{new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 77}};
  std::cout << arr_ptr[4] << std::endl;

  Unique_ptr<debug[]> ptr_{new debug[5]{}};
  Unique_ptr<debug> ptr1_{new debug{}};
  auto file = std::fopen("my_text.txt", "r");
  Unique_ptr<FILE, decltype(&fclose)> ptrFile{file};

  return 0;
}
