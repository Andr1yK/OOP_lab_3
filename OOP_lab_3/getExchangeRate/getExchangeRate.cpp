//
//  getExchangeRate.cpp
//  OOP_lab_3
//
//  Created by Andriy Kobetiak on 10.10.2022.
//

#include "getExchangeRate.hpp"

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

double getExchangeRate() {
  std::string rate = exec("curl -s 'https://v6.exchangerate-api.com/v6/0d79054d61b26899a09c683a/pair/UAH/USD' | \
    python3 -c \"import sys, json; print(json.load(sys.stdin)['conversion_rate'])\"");
  
  return atof(rate.c_str());
}
