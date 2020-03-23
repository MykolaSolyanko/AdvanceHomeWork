#include "Vector.h"
#include <iostream>

class A {
public:
  A() = default;
  A(int size) :a(size) { }
  A(int size, double d) :a(size),y(d){}
  A(const A&) {}
  A(A&&) {}
  A operator =(const A&) {return *this; }
  A operator =(A&&) {return *this; }
private:
  int a;
  double y;
};



int main() {
  Vector<int>v;
	v.insert(5, 3);
	v.push_back(3);
	v.reserve(10);
	v.resize(6);
	v.pop_back();
	Vector<int>v1(v);
	Vector<A>vA(4);
	v.emplace_back(1);
	v.push_front(9);
	Vector<A>vA1(vA);
	vA1.pop_back();
	vA1.push_front(55);
	vA1.erase(66);
	vA = vA1;
	vA1 = Vector<A>(8);

	Stack<char>st;
	st.push('r');
	st.pop();
	st.push('R');
	st.push('Y');
	st.top();
	Stack<char>st1 = st;

	Stack<A>stA(99);
	stA.push(4);
	stA.push(6578);
	stA.push(55);
	stA.pop();
	stA.top();

  return 0;
};
