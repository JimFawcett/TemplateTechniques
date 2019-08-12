///////////////////////////////////////////////////////////////////////
//  FuncPtr.cpp  -  demonstrating some unusual template definitions  //
//                                                                   //
//     Refer to Stroustrup, 13.2.3 - Template Parameters             //
//                                                                   //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004        //
///////////////////////////////////////////////////////////////////////
//
// To keep this demo simple I've placed the template definitions
// along with the test code in the same cpp file.  Normally you
// will place all template definitions in a separate header file.
//
#include <iostream>
using namespace std;

//----< declare two simple functions >-------------------------------

void fun1() { cout << "\n  this is fun1"; }

void fun2() { cout << "\n  this is fun2"; }

//----< declare template class taking function pointer parameter >---

template <void(*f)()>
class templ1 {

  string str;

  public:
    void show() { f(); }
};

//----< declare strings with external linkage >----------------------
//
//  Non-type template arguments must be integral or be pointers
//  with external linkage (Stroustrup, 13.2.3), so s1 and s2
//  must be global to use as template arguments.

char *s1 = "first string";

char *s2 = "second string";

//----< declare template class taking pointer to C string >----------

template <char **s>
class templ2 {

  public:
    void show() { cout << "\n  " << (*s); }
};

//

//----< test unusual template definitions >--------------------------

void main() {

  cout << "\n  Demonstrating use of templates with unusual parameters "
       << "\n ========================================================\n";

  templ1<fun1> tl;
  tl.show();

  templ1<fun2> t2;
  t2.show();

  cout << '\n';

  templ2<&s1> t3;
  t3.show();

  templ2<&s2> t4;
  t4.show();

  cout << "\n\n";
}
