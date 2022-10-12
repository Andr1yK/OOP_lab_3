//
//  main.cpp
//  OOP_lab_3
//
//  Created by Andriy Kobetiak on 10.10.2022.
//

#include <iostream>
#include "Account.hpp"

int main() {
  srand(static_cast<unsigned int>(time(nullptr)));

  Account* acc1 = new Account();
  cout << acc1->toString() << endl << endl;

  Account acc2 = Account("Michael");
  cout << acc2.toString() << endl << endl;

  acc2.changeOwner("Stafford");
  acc2.Display();

  Account acc3 = Account("Hansen", 100);
  acc3.Display();
  
  acc3.accrueInterest();
  acc3.accrueInterest();
  
  acc3.withdrawMoney(1000);
  
  acc3.Display();

  Account acc4 = Account("Forbes", 7312.89, 6.5);
  acc4.Display();
  
  cout << acc4.getMoney() << " UAH ≈ "
    << acc4.convertToUSD() << " USD" << endl << endl;
  
  
  Account acc5 = Account(acc4);
  acc5.Display();

  acc4.depositMoney(12345678954341);
  
  acc4.Display();
  
  cout << acc4.convertToString() << endl << endl;

  delete acc1;

  return 0;
}
