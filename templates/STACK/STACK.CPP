///////////////////////////////////////////////////////////////////////
// Stack.cpp - stack class derived from Effective C++, Scott Meyers  //
//                                                                   //
//   Note: inclusion model for templates requires all template       //
//         implementations be placed in header file.                 //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004         //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include "stack.h"
using namespace std;

template <class T> void print_field(T t) {  // template function

  cout.width(10);
  cout << t;
}
//----< test stub >--------------------------------------------------
void main() {

  cout << "\nTesting Template Based Stack Class\n";

  try
  {
    stack<int>    int_stack;
    stack<double> double_stack;

    int    x=1,    y=2,   z=3;
    double u=-1.5, v=0.5, w=2.5;

    cout << "\n  pushing stack: "; print_field(x); int_stack.push(x);
    cout << "\n  pushing stack: "; print_field(y); int_stack.push(y);
    cout << "\n  pushing stack: "; print_field(z); int_stack.push(z);
    cout << endl;
    cout << "\n  stack size = " << int_stack.size() << endl;

    stack<double> copyStack = int_stack;  // copy construction
                                          //   with data conversion

    cout << "\n  popping stack: "; print_field(int_stack.pop());
    cout << "\n  popping stack: "; print_field(int_stack.pop());
    cout << "\n  popping stack: "; print_field(int_stack.pop());
    cout << "\n";

    cout << "\n  stack size = " << int_stack.size() << endl;

    cout << "\n  popping double copy of int stack:";
    cout << "\n  popping stack: "; print_field(copyStack.pop());
    cout << "\n  popping stack: "; print_field(copyStack.pop());
    cout << "\n  popping stack: "; print_field(copyStack.pop());
    cout << "\n";

    cout << "\n  pushing stack: "; print_field(u); double_stack.push(u);
    cout << "\n  pushing stack: "; print_field(v); double_stack.push(v);
    cout << "\n  pushing stack: "; print_field(w); double_stack.push(w);
    cout << endl;

//
    stack<int> int2_stack;
    int2_stack = double_stack;  // assignment with data conversion

    cout << "\n  popping stack: "; print_field(double_stack.pop());
    cout << "\n  popping stack: "; print_field(double_stack.pop());
    cout << "\n  popping stack: "; print_field(double_stack.pop());
    cout << "\n";

    cout << "\n  popping int copy of double stack:";
    cout << "\n  popping stack: "; print_field(int2_stack.pop());
    cout << "\n  popping stack: "; print_field(int2_stack.pop());
    cout << "\n  popping stack: "; print_field(int2_stack.pop());
    cout << "\n";

    int2_stack.pop(); // popping empty stack

    cout << "\n\n";
  }
  catch(exception& ex)
  {
    cout << "\n  " << ex.what() << endl;
  }
  catch(...)
  {
    cout << "\n  stack error\n\n";
  }
}
