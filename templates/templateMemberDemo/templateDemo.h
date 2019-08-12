#ifndef TEMPLATEDEMO_H
#define TEMPLATEDEMO_H
/////////////////////////////////////////////////
// template demo.h
//
// classes classTemplate and modifiedClassTemplate 
// demonstrate full class templates under inheritance
//
// classes memberTemplate and modifiedMemberTemplate
// show how that changes for member templates
//

#include <sstream>

/////////////////////////////////////////////////
// class classTemplate<T>

template <typename T>
class classTemplate
{
public:
  classTemplate(T t);
  virtual ~classTemplate();
  virtual std::string announce();
  std::string message();
protected:
  T _t;
};

template<typename T>
classTemplate<T>::classTemplate(T t) : _t(t) {}

template<typename T>
classTemplate<T>::~classTemplate() {}

template<typename T>
std::string classTemplate<T>::announce()
{
  std::string temp = message();
  temp += "\n  base class classTemp<T>\n";
  return temp;
}

template<typename T>
std::string classTemplate<T>::message()
{
  std::ostringstream temp;
  temp << "\n  template parameter value = " << _t;
  return temp.str();
}

/////////////////////////////////////////////////
// class modifiedClassTemplate<T>

template <typename T>
class modifiedClassTemplate : public classTemplate<T>
{
public:
  modifiedClassTemplate(T t);
  ~modifiedClassTemplate() {}
  std::string announce();
};

template <typename T>
modifiedClassTemplate<T>::modifiedClassTemplate(T t) : classTemplate<T>(t) {}

template<typename T>
std::string modifiedClassTemplate<T>::announce()
{
  std::string temp = message();
  temp += "\n  derived class modifiedClassTemp<T>\n";
  return temp;
}

/////////////////////////////////////////////////
// class memberTemplate

class memberTemplate
{
public:
  virtual ~memberTemplate() {}
  template<typename T> std::string announce(T t);  // can't be virtual
  virtual std::string message();
};

std::string memberTemplate::message() { return "\n  memberTemplate: "; }

template <typename T>
std::string memberTemplate::announce(T t)
{
  ostringstream build;
  build << message();
  build << "value of template parameter = " << t;
  return build.str();
}

/////////////////////////////////////////////////
// class modifiedMemberTemplate

class modifiedMemberTemplate : public memberTemplate
{
public:
  virtual ~modifiedMemberTemplate() {}
  virtual std::string message();
};

std::string modifiedMemberTemplate::message() { 
  return "\n  modifiedMemberTemplate: "; 
}

#endif
