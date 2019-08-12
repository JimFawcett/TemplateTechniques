/////////////////////////////////////////////////
// templateDemo.h

#include <iostream>
#include "templateDemo.h"
using namespace std;

int main()
{
  cout << "\n  Template Class and Template Member Demo "
       << "\n =========================================\n";

  classTemplate<double> ct(3.1415927);
  cout << ct.announce();

  modifiedClassTemplate<int> mct(-15);
  cout << mct.announce();

  cout << "\n";

  memberTemplate mt;
  cout << mt.announce(3.1415927);
  
  cout << "\n";

  modifiedMemberTemplate mmt;
  cout << mmt.announce(-15);

  cout << "\n\n";
}