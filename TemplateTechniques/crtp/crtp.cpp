/////////////////////////////////////////////////////////////////////
// crtp.cpp - Curiously Recurring Template Pattern                 //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2006       //
/////////////////////////////////////////////////////////////////////

#include "crtp.h"

int main(int argc, char* argv[])
{
  std::cout << "\n  Demonstrating Curiously Recurring Template Pattern";
  std::cout << "\n ====================================================\n";

  modifiedAlgorithm ma1;
  std::cout << std::endl;

  algorithmWithSteps<modifiedAlgorithm>* pAlgor = ma1.doAlgorithm();
  std::cout << "\n  step3() in doAlgorithm() returned a pointer to " << typeid(*pAlgor).name();
  std::cout << std::endl;
  pAlgor->doAlgorithm();

  std::cout << "\n\n";
}
