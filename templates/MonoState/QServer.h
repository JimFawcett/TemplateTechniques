#ifndef QUEUESERVER_H
#define QUEUESERVER_H
/////////////////////////////////////////////////////////////////////
// QServer.h - serves out references to a static queue             //
//                                                                 //
//     For each type T and for each integer qNum, we get           //
//     one QServer  class and one shared queue.                    //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////
//
//  This class is an instance of the Monstate Pattern.
//  Monostate classes act like safe global data.  
//  - Their data is static and so shared by all users.
//  - Two pieces of code, in possibly different scopes, that 
//    create instances of the class, get access to the same
//    data without passing it into their scope by other means.
//  - Since the data is available through class member functions,
//    unlike global data, its access can be controlled, inputs 
//    validated, and usage logged.
//  - This particular class uses the T parameter to defer choice
//    of the queue contents until design of a using application.
//    T could be a double, as illustrated here, or perhaps an XML
//    Message.
//  - The integer template parameter is used to segregate user
//    sharing into groups.  All users of QServer<T,1> share the
//    same queue, but do not share a queue with users of
//    QServer<T,2>.
//  - Normally we share queues between threads, so to be useful,
//    this class would need to provide serialized access to its
//    queues, perhaps through a lock class based on critical 
//    sections.

#include <queue>  // STL container

template <typename T, int qNum> class QServer
{
public:
  std::queue<T>& get() { return _q; }
private:
  static std::queue<T> _q;
};

// define static member _q

template<typename T, int qNum> std::queue<T> QServer<T,qNum>::_q;

#endif
