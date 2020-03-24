#include "vector.hpp"
#include "array.hpp"
#include <iostream>
#include <string>

void show_vector(Vector<Array>&vec) {
    std::cout << "SIZE: " << vec.size() << "  CAPACITY: " << vec.capacity() << "\nDATA: \n";
    for(size_t i{0}; i < vec.size(); ++i) {
        vec[i].print(" ");
    }
}

void line(const char* s) {
    std::cout << "\n************ " << s << " ************\n";
}
int main() {  
    line("--------- DEMONSTRATE ARRAY CLASS WHICH WILL BE USED TO TEST VECTOR ---------");

    line("CREATE OBJECTS");
    //Default Constructor
    Array a1;   
    // User Constructor
    Array a2(4), a3(8); 
    a1.print("a1");
    a2.print("a2");
    a3.print("a3");

    line("COPY CONSTRUCTOR");
    a2.print("a2");
    Array a4(a2);
    a2.print("a2");
    a4.print("a4");

    line("MOVE CONSTRUCTOR");
    a3.print("a3");
    Array a5(std::move(a3));
    a3.print("a3");
    a5.print("a5");

    line("COPY ASSIGNMENT");
    a1.print("a1");
    a2.print("a2");
    a1 = a2;
    a1.print("a1");
    a2.print("a2");

    line("MOVE ASSIGNMENT");
    a3.print("a3");
    a4.print("a4");
    a3 = std::move(a4);
    a3.print("a3");
    a4.print("a4");

    line("DESTRUCTOR");
    {
        Array a6;
    }

    line("--------- DEMONSTRATE VECTOR CLASS ---------");

    line("DEFAULT CTOR");
    Vector<Array> v0;

    line("CTOR 1 - SIZE");    
    Vector<Array> v1(3);

    line("CTOR 2 - INITIALIZER LIST");
    Vector<Array> v2({Array(1), Array(2)});

    line("CTOR 3 - BEGIN, END");
    const size_t SIZE{5};
    Array a[SIZE]{Array(1), Array(2), Array(4), Array(6), Array(8)};
    Vector<Array>v3(a, a + 3);

    line("COPY CTOR");
    Vector<Array> v4(3);
    Vector<Array> v5(v4);

    line("COPY ASSIGNMENT");
    Vector<Array> v6(1);
    Vector<Array> v7(2);
    v6 = v7;

    line("MOVE CTOR");
    Vector<Array> v8(2);
    Vector<Array> v9(std::move(v8));

    line("MOVE ASSIGNMENT");
    Vector<Array> v10(1);
    Vector<Array> v11(2);
    v11 = std::move(v10);

    line("PUSH FRONT LVAL");
    Array b;
    Vector<Array> v12(2);
    v12.push_front(b);

    line("PUSH FRONT RVAL"); 
    Vector<Array> v13(3);
    v13.push_front(Array(15));

    line("PUSH BACK LVAL");
    Array b1(3);
    Vector<Array>v14;
    v14.reserve(3);
    v14.push_back(b1);

    line("PUSH BACK RVAL"); 
    Array b2(3);
    Vector<Array>v15(2);
    v15.push_back(std::move(b2));    

    line("EMPLACE BACK LVAL");
    Array b3(100);
    Vector<Array>v16;
    v16.reserve(3);
    v16.emplace_back(b3);

    line("EMPLACE BACK RVAL");
    Array b4(3);
    Vector<Array>v17;
    v17.reserve(3);
    v17.emplace_back(std::move(b4));

    line("EMPLACE BACK - PROVIDE CTOR ARGS");
    Vector<Array>v18;
    v18.reserve(3);
    const size_t SIZE_{5};
    v18.emplace_back(SIZE_);

    line("END");
    return 0;
}