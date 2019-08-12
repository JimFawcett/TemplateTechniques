/////////////////////////////////////////////////////////////////
//  invoker1.cpp - defines classes to wrap function pointers   //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 05    //
/////////////////////////////////////////////////////////////////

#include <vector>

///////////////////////////////////////////////////////////
// delegate for global functions of the form 
// R fun(A a)

template <class R, class A>
class delegate
{
public:
  typedef R(*funPtr)(A);

  void add(funPtr pF)
  {
    doCall.push_back(pF);
  }
  R invoke(A a)
  {
    R retVal;
    for(size_t i=0; i<doCall.size(); ++i)
      retVal = doCall[i](a);
    return retVal;
  }
  R operator()(A a)
  {
    return invoke(a);
  }
private:
  std::vector<funPtr> doCall;
};

///////////////////////////////////////////////////////////
// specialized delegate for global functions of the form
// void fun(A a)

template <class A>
class delegate<void, A>
{
public:
  typedef void(*funPtr)(A);

  void add(funPtr pF)
  {
    doCall.push_back(pF);
  }
  void invoke(A a)
  {
    for(size_t i=0; i<doCall.size(); ++i)
      doCall[i](a);
  }
  void operator()(A a)
  {
    invoke(a);
  }
private:
  std::vector<funPtr> doCall;
};

///////////////////////////////////////////////////////////
// delegate for member functions of the form
// void T::fun(A a)

template <class T, class A>
class mdelegate
{
public:
  typedef void(T::*fPtr)(A);

  void add(T* pObj, fPtr pF)
  {
    std::pair<T*,fPtr> item;
    item.first = pObj;
    item.second = pF;
    doCall.push_back(item);
  }

  void invoke(A a)
  {
    for(size_t i=0; i<doCall.size(); ++i)
    {
      std::pair<T*, fPtr> item;
      item = doCall[i];
      T* pObject = doCall[i].first;
      fPtr f = doCall[i].second;
      (pObject->*f)(a);
      
      ////////////////////////////////////////////
      // this works too
      // ((doCall[i].first)->*doCall[i].second)(a);
    }
  }
  void operator()(A a)
  {
    invoke(a);
  }
private:
  std::vector< std::pair<T*,fPtr> > doCall;
};

//----< demonstrate invoker >----------------------------------------

#include <iostream>

double trunc(double d)
{
  double temp;
  std::cout << "\n  truncating " << d << " to obtain: " << (temp = static_cast<int>(d));
  return temp;
}

double square(double d)
{
  double temp;
  std::cout << "\n  squaring " << d << " to obtain: " << (temp = d*d);
  return temp;
}

void squareNoReturn(double d)
{
  std::cout << "\n  squaring " << d << " to obtain: " << d*d;
}

struct Args
{
  int i;
  double d;
};

void simulateArgs(Args& a)
{
  std::cout << "\n  1st arg = " << a.i;
  std::cout << "\n  2nd arg = " << a.d;
}

class X
{
public:
  X(int y) : multiplier(y) {}
  void fun(int i) 
  { 
    std::cout << "\n  multiplying input " << i
              << " by member value " << multiplier 
              << " to obtain " << multiplier*i; 
  }
private:
  int multiplier;
};

void main()
{
  std::cout << "\n  Demonstrating Template-based Delegates";
  std::cout << "\n ========================================\n";

  std::cout << "\n  testing delegate for functions R fun(A a)";
  std::cout << "\n -------------------------------------------";
  delegate<double, double> testdel;
  testdel.add(trunc);
  testdel.add(square);
  double ret = testdel.invoke(1.11111);
  std::cout << "\n  return value is " << ret;
  std::cout << std::endl;

  std::cout << "\n  testing delegate for function void fun(A a)";
  std::cout << "\n ---------------------------------------------";
  delegate<void, double> testdelNoReturn;
  testdelNoReturn.add(squareNoReturn);
  testdelNoReturn(6);
  std::cout << std::endl;

  std::cout << "\n  testing delegate for functions with several arguments";
  std::cout << "\n -------------------------------------------------------";
  delegate<void, Args&> argsdel;
  Args a = { -3, 3.1415927 };
  argsdel.add(simulateArgs);
  argsdel.invoke(a);
  a.i = 3;
  a.d = 0.333333333;
  argsdel(a);
  std::cout << std::endl;


  std::cout << "\n  testing delegate for member function void T::fun(A a)";
  std::cout << "\n -------------------------------------------------------";
  X x1(2), x2(3);
  mdelegate<X, int> mdel;
  mdel.add(&x1, &X::fun);
  mdel.add(&x2, &X::fun);
  mdel.invoke(3);
  mdel(17);
  std::cout << std::endl;

  std::cout << "\n\n";
}
