///////////////////////////////////////////////////////////////////////
// Client.cpp - client of max<T> template

#include <iostream>
#include "../max/max.h"

int main()
{
  std::cout << "\n  Demonstrating Simple Specialization";
  std::cout << "\n =====================================\n";

  int small = 2, large = 200;
  std::cout << "\n  max(2,200) = " << ::max(2,200) << "\n";

  std::cout << "\n  max(\"ardvarkk\",\"zebra\") = " 
    << ::max((char*)"ardvarkk",(char*)"zebra") << "\n\n";

}

