#include "Vector.h"
#include <iostream>

int main() {
  Stack<int>stack(5);
  Stack<int>stack1(stack);
  Stack<int>stack2 = stack1;
  stack = stack2;

  stack.push(5);
  stack.push(6);
  stack.pop();
  stack.push(7);
  stack.top();

  return 0;
};
