#include "shared_ptr.hpp"
#include <iostream>

class debug {
public:
  ~debug() { std::cout << "~debug()" << std::endl; }
};

int main() {
  Shared_ptr<int> ptr{new int{6}};
  Shared_ptr<int> ptr1{ptr};
  std::cout << ptr.use_count() << std::endl;
  std::cout << *ptr.get() << std::endl;
  ptr.reset(new int{55});
  std::cout << ptr.use_count() << std::endl;
  std::cout << *ptr.get() << std::endl;
  std::cout << ptr1.use_count() << std::endl;
  std::cout << *ptr1.get() << std::endl;

  Shared_ptr<debug> ptrD{new debug{}};
  Shared_ptr<debug[]> ptrDq{new debug[5]{}};
  Shared_ptr<debug[]> prt_copy{ptrDq};
  std::cout << prt_copy.use_count() << std::endl;
  return 0;
}
