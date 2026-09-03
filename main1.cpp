#include <iostream>
#include <string>
#include <vector>
#include "stdc++.h"


std::vector<std::string> token(std::string user_input);

int main() {
  std::string user_input;
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::cout << "$ ";
  std::getline(std::cin,user_input);
}


/*token maker*/
std::vector<std::string> token(std::string user_input){
    std::vector<std::string> tokens;
    std::stringstream check1(user_input);
    std::string temp;
     while(getline(check1, temp, ' '))
    {
        tokens.push_back(temp);
    }
    return tokens;
}