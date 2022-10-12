//
//  Account.hpp
//  OOP_lab_3
//
//  Created by Andriy Kobetiak on 10.10.2022.
//

#ifndef Account_hpp
#define Account_hpp

#include <string>
#include <cmath>
#include "getExchangeRate.hpp"

using namespace std;

class Account {
private:
  static int count;

  string lastName;
  unsigned int id;
  double percentIncome;
  double money;

  static string generateRandomeName(unsigned int length);

  static bool isValid(string, double = 0, double = 10);

  static string convertGroupOfThree(int, int = 0);
  static string getHundreds(int);
  static string getCorrectThousandsName(unsigned long long int);
  static function<string(unsigned long long int)> getCorrectName(string);

public:
  Account();
  Account(string);
  Account(string, double);
  Account(string, double, double);
  Account(Account&);
  ~Account();

  double getMoney() { return this->money; };
  unsigned int getID() { return this->id; };
  string getLastName() { return this->lastName; };

  string toString();
  void Display();
  
  bool changeOwner(string);
  
  bool withdrawMoney(double);
  bool depositMoney(double);

  double accrueInterest();

  double convertToUSD();
  string convertToString();
};

#endif /* Account_hpp */
