#include "unique_ptr.hpp"

// custom destructor function
void my_dtor(int *a) {
  std::cout << "MY DESTRUCTOR GOT CALLED\n";
  delete[] a;
}

// print content of pointer
void print(const char *text, int *ptr) {
  std::cout << text << " ";
  if (ptr == nullptr) {
    std::cout << "Empty\n";
  } else {
    std::cout << *ptr << std::endl;
  }
}

// print content of array
void print_array(const char *text, int *array, size_t size) {
  std::cout << text << " ";
  if (array == nullptr) {
    std::cout << "Empty\n";
  } else {
    for (size_t i{0}; i < size; ++i) {
      std::cout << array[i] << " ";
    }
    std::cout << std::endl;
  }
}

// DEMO
int main() {

  std::cout << "\n************ TEST 1 - Destructor Demo ************\n";
  int *raw_ptr = new int{999};
  print("Raw pointer:", raw_ptr);
  { unique_ptr<int> A(raw_ptr); }
  print("Raw pointer:", raw_ptr);

  std::cout << "\n************ TEST 2 - Move Constructor ************\n";
  unique_ptr<int> B1(new int{80});
  print("B1:", B1.get());
  unique_ptr<int> B2(std::move(B1));
  print("B1:", B1.get());
  print("B2:", B2.get());

  std::cout << "\n************ TEST 3 - Move Assignment ************\n";
  unique_ptr<int> C1(new int{500});
  unique_ptr<int> C2;
  print("C1:", C1.get());
  print("C2:", C2.get());
  C2 = std::move(C1);
  print("C1:", C1.get());
  print("C2:", C2.get());

  std::cout << "\n************ TEST 4 - Release ************\n";
  int *array = new int[5]{1, 2, 3, 4, 5};
  unique_ptr<int[]> D1(array);
  print_array("Array initial:", array, 5);
  print_array("D1 initial:", D1.get(), 5);
  D1.release();
  print_array("Array after release:", array, 5);
  print_array("D1 after release:", D1.get(), 5);
  delete[] array;

  std::cout << "\n************ TEST 5 - Reset ************\n";
  int *array1 = new int[3]{100, 300, 500};
  int *array2 = new int[4]{200, 400, 600, 800};
  unique_ptr<int[]> E1(array1);
  print_array("Array1 initial:", array1, 3);
  print_array("E1 initial:", E1.get(), 3);
  E1.reset(array2);
  print_array("Array1 after reset:", array1, 3);
  print_array("E1 after reset:", E1.get(), 4);

  std::cout << "\n************ TEST 6 - Custom Delete ************\n";
  unique_ptr<int, decltype(my_dtor)> F1(new int[3]{-10, -20, -30}, my_dtor);
  unique_ptr<int, decltype(my_dtor)> F2(new int[8]{1, 2, 3, 4, 5, 6, 7, 8},
                                        my_dtor);
  print_array("F1:", F1.get(), 3);
  print_array("F2:", F2.get(), 8);
  F1 = std::move(F2);
  print_array("F1:", F1.get(), 8);
  print_array("F2:", F2.get(), 8);
  return 0;
}
