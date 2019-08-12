#ifndef STACK_H
#define STACK_H
///////////////////////////////////////////////////////////////////////
// Stack.h - stack class derived from Effective C++, Scott Meyers    //
//                                                                   //
//   Note: inclusion model for templates requires all template       //
//         implementations be placed in header file.                 //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004         //
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////
// template class 

template<class T> class stack {

  template <class U> friend class stack;

  private:
    struct stacknode {
      T data;
      stacknode *next;
      stacknode(const T& newdata, stacknode *nextnode)
	       : data(newdata), next(nextnode) { }
    };
    stacknode *top;
  public:
    stack();
    ~stack();
    void push(const T& object);
    T pop(void);
    void flush();
    int size() const;
    
    // member templates

    template <class U> stack(const stack<U>&);
    template <class U> stack<T>& operator=(const stack<U>&);
};

//
//----< void constructor >---------------------------------------------

template<class T> stack<T>::stack() : top(0) { }

//----< destructor >---------------------------------------------------

template <class T> stack<T>::~stack(void) {

  while (top) {
    stacknode *next_to_die = top;
    top = top->next;
    delete next_to_die;
  }
}
//----< push data onto stack >-----------------------------------------

template<class T> void stack<T>::push(const T &object) {
  top = new stacknode(object, top);
}
//----< pop data from stack >------------------------------------------

template <class T> T stack<T>::pop(void) {

  if (!top) {
    throw std::out_of_range("\n  attempt to pop empty stack\n");
  }
  stacknode *save = top;
  top = top->next;
  T data = save->data;
  delete save;
  return data;
}
//----< empty stack >--------------------------------------------------

template <class T> void stack<T>::flush()
{
  stacknode* node = top;
  while(node)
  {
    stacknode *next_to_die = node;
    node = node->next;
    delete next_to_die;
  }
}
//----< return number of elements on stack >---------------------------

template <class T> int stack<T>::size() const
{
  stacknode* node = top;
  int count = 0;
  while(node)
  {
    count++;
    node = node->next;
  }
  return count;
}
//
//----< copy and promotion constructor, a member template >------------

template <class T> 
template <class U> stack<T>::stack(const stack<U>& s) : top(0)
{
  stack<U>::stacknode* node = const_cast<stack<U>::stacknode*>(s.top);
  while(node)
  {
    this->push(node->data);
    node = node->next;
  }
}
//----< assignment from stack of possibly a compatible type >----------

template <class T> 
template <class U> stack<T>& stack<T>::operator=(const stack<U>& s)
{
  if((void*)this == (void*)&s)
    return *this;

  flush();
  stack<U>::stacknode* node2 = const_cast<stack<U>::stacknode*>(s.top);
  while(node2)
  {
    this->push(static_cast<T>(node2->data));
    node2 = node2->next;
  }
  return *this;
}
#endif
