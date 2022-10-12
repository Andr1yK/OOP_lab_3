//
//  Account.cpp
//  OOP_lab_3
//
//  Created by Andriy Kobetiak on 10.10.2022.
//

#include "Account.hpp"

using namespace std;

unsigned long long MAX_COUNT_OF_MONEY = std::numeric_limits<unsigned long long int>::max();

string const specialHundredsCases[] = {
  "сто ",
  "двісті ",
  "триста ",
  "чотириста ",
  "п'ятсот ",
  "шістсот ",
  "сімсот ",
  "вісімсот ",
  "дев'ятсот "
};

int Account::count = 0;

bool Account::isValid(string lastName, double money, double percentIncome) {
  if (lastName.length() <= 5) {
    throw std::invalid_argument(
      "ERROR: Last name is too short (min 5 letters)\n\n"
    );
  }

  if (money < 0) {
    throw std::invalid_argument(
      "ERROR: We do not issue loans, the minimum starting amount must be at least 0"
    );
  }

  if (money > MAX_COUNT_OF_MONEY) {
    throw std::invalid_argument(
      "ERROR: You are too rich, the maximum allowed count of money is "
      + to_string(MAX_COUNT_OF_MONEY)
    );
  }

  if (percentIncome < 0) {
    throw std::invalid_argument("ERROR: Income cannot be negative");
  }
  
  return true;
}

Account::Account() {
  this->id = ++Account::count;
  
  this->lastName = Account::generateRandomeName((rand()%10)+5);
  this->money = 0;
  this->percentIncome = 10;
}

Account::Account(string lastName) {
  Account::isValid(lastName); // like a midleware
  
  this->id = ++Account::count;
  
  this->lastName = lastName;
  this->money = 0;
  this->percentIncome = 10;
}

Account::Account(string lastName, double money) {
  Account::isValid(lastName, money); // like a midleware
  
  this->id = ++Account::count;
  
  this->lastName = lastName;
  this->money = money;
  this->percentIncome = 10;
}

Account::Account(string lastName, double money, double percentIncome) {
  Account::isValid(lastName, money, percentIncome); // like a midleware

  this->id = ++Account::count;

  this->lastName = lastName;
  this->money = money;
  this->percentIncome = percentIncome;
}

Account::Account(Account& account) {
  this->id = ++Account::count;
  
  this->lastName = account.lastName;
  this->money = account.money;
  this->percentIncome = account.percentIncome;
}

Account::~Account() {
  printf("I am destructor for account with ID %i\n", this->id);
}

string Account::toString() {
  const string ID = "Account ID: " + to_string(this->id);
  const string LastName = "Last name: " + this->lastName;
  const string Money = "Money: " + to_string(this->money) + " UAH";
  const string PercentIncome = "Percent income: " + to_string(this->percentIncome) + '%';

  return ID + '\n' + LastName + '\n' + Money + '\n' + PercentIncome;
}

void Account::Display() {
  printf("INFO:\n%s\n\n", this->toString().c_str());
}

bool Account::changeOwner(string owner) {
  if (Account::isValid(owner)) {
    this->lastName = owner;
  }

  return true;
}

bool Account::withdrawMoney(double count) {
  if (this->money - count < 0) {
    printf("WARN: There are not enough funds on the account\n\n");

    return false;
  }

  this->money -= count;

  return true;
}

bool Account::depositMoney(double count) {
  if (count <= 0) {
    printf("WARN: You cannot top up your account with a negative amount or 0\n\n");
    
    return false;
  }

  this->money += count;

  return true;
}

double Account::accrueInterest() {
  this->money *= this->percentIncome / 100 + 1;

  return this->money;
}

double Account::convertToUSD() {
  const double rate = getExchangeRate();

  return this->money * rate;
}

string Account::convertToString() {
  unsigned long long int num = this->money;

  if (!num) {
    return "нуль";
  }

  unsigned long long int rest = static_cast<long long int>(this->money*100)%100;

  function<string(unsigned long long)> getCorrect[] = {
    [](long int) {return "";},
    Account::getCorrectThousandsName,
    Account::getCorrectName("мільйон"),
    Account::getCorrectName("мільярд"),
    Account::getCorrectName("трильйон"),
    Account::getCorrectName("квадрильйон"),
    Account::getCorrectName("квінтильйон"),
  };

  string coins = rest
    ? Account::convertGroupOfThree(rest, 1)
    : "нуль ";
  string result = "грн. " + coins + "коп.";

  int place = 0;

  do {
    if (!num) {
      break;
    }

    int first_three_digits = num % 1000;

    string temp = Account::convertGroupOfThree(first_three_digits, place);

    result = (temp != ""
      ? temp + getCorrect[place](num)
      : ""
      ) + result;

    num /= 1000;

    place += 1;
  } while(1);

  return result;
}

// --- HELPERS ---
string Account::generateRandomeName(unsigned int length) {
  char consonents[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','z'};
  char vowels[] = {'a','e','i','o','u','y'};

  string name = "";

  int random = rand() % 2;
  int count = 0;

  for(int i = 0; i < length; i++) {
    if(random < 2 && count < 2) {
      name = name + consonents[rand() % 19];
      count++;
    }
    else {
      name = name + vowels[rand() % 5];
      count = 0;
    }

    random = rand() % 2;
  }

  return name;
}

// --- CONVERT HELPERS ---

string Account::convertGroupOfThree(int num, int place) {
  const int specialCasesLenght = 20;
  string specialCases[specialCasesLenght] = {
    "",
    place == 1 ? "одна " : "один ",
    place == 1 ? "дві " : "два ",
    "три ",
    "чотири ",
    "п'ять ",
    "шість ",
    "сім ",
    "вісім ",
    "дев'ять ",
    "десять ",
    "одинадцять ",
    "дванадцять ",
    "тринадцять ",
    "чотирнадцять ",
    "п'ятнадцять ",
    "шістнадцять ",
    "сімнадцять ",
    "вісімнадцять ",
    "дев'ятнадцять "
  };

  if (num < specialCasesLenght) {
    return specialCases[num % 100];
  }

  if (num % 100 < specialCasesLenght) {
    return getHundreds(num / 100) + specialCases[num % 100];
  }

  int first_digit = num % 10;
  num /= 10;

  string result = specialCases[first_digit];

  int second_digit = num % 10;
  num /= 10;

  switch (second_digit) {
    case 2:
      result = "двадцять " + result;
      break;
    case 3:
      result = "тридцять " + result;
      break;
    case 4:
      result = "сорок " + result;
      break;
    case 5:
      result = "п'ятдесят " + result;
      break;
    case 6:
      result = "шістдесят " + result;
      break;
    case 7:
      result = "сімдесят " + result;
      break;
    case 8:
      result = "вісімдесят " + result;
      break;
    case 9:
      result = "дев'яносто " + result;
      break;
    default:
      break;
  }

  return getHundreds(num) + result;
}

string Account::getHundreds(int num) {
  if (num > 9 || num < 1) {
    return "";
  }

  return specialHundredsCases[num - 1];
}

string Account::getCorrectThousandsName(unsigned long long int num) {
  if (num % 100 > 10 && num % 100 < 20) {
    return "тисяч ";
  }

  if (num % 10 == 1) {
    return "тисяча ";
  }

  if (num % 10 >= 2 && num % 10 <= 4) {
    return "тисячі ";
  }
  
  return "тисяч ";
}

function<string(unsigned long long int)> Account::getCorrectName(string baseWord) {
  return [baseWord](unsigned long long int num) -> string {
    if (num % 100 > 10 && num % 100 < 20) {
      return baseWord + "ів ";
    }

    if (num % 10 >= 2 && num % 10 <= 4) {
      return baseWord + "и ";
    }

    if ((num / 1000 == 0 || num / 1000 == 5) && num % 10 == 1) {
      return baseWord + " ";
    }
    
    return baseWord + "ів ";
  };
}
