/////////////////////////////////////////////////////////////////////
// QServer.cpp - serves out references to a static queue           //
//                                                                 //
//     For each type T and for each integer qNum, we get           //
//     one QServer  class and one shared queue.                    //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include "QServer.h"
using namespace std;

void PopAndShow(queue<double>& q)
{
  long save = cout.flags();    // save format state
  cout.flags(ios::showpoint);  // show decimal point
  cout.precision(3);           // show only 3 digits on right of decimal
  cout << "\n  " << setw(4) << q.front() << " : ";  
  q.pop(); 
  cout << "Q size = " << q.size();
  cout.flags(save);            // restore format state
}

int main()
{
  cout << "\n  Demonstrating Queue Server holding Static Queue "
       << "\n =================================================";

  // get shared queue

  queue<double> &q1 = QServer<double,1>().get();
  q1.push(1.0);
  q1.push(1.5);
  q1.push(2.0);

  // get shared queue again

  queue<double> &q2 = QServer<double,1>().get();
  q2.push(2.5);
  q2.push(3.0);
  q2.push(3.5);

  ///////////////////////////////////////////////////////////////////
  // QServer<double,2> is different class than QServer<double,1>
  // so static queue member is not shared between them.

  // get unshared queue

  queue<double> &q3 = QServer<double,2>().get();
  q3.push(-2.5);
  q3.push(-3.0);
  q3.push(-3.5);

  cout << "\n  ";
  while(q1.size() > 0)
    PopAndShow(q1);
  cout << "\n\n";

  while(q3.size() > 0)
    PopAndShow(q3);
  cout << "\n\n";
  return 0;
}