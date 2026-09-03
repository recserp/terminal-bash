#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include "stdc++.h"


std::vector<std::string> token(std::string user_input);
void echo(std::vector<std::string> tokens);
bool error(std::string user_input);
void type(std::vector<std::string> tokens);

std::unordered_set<std::string> valid_command = {"exit","echo","type"}; 

int main() {
  std::string user_input;
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  char a = 'a';


  while(a == 'a'){
    std::cout << "$ ";
    std::getline(std::cin,user_input);
    std::vector<std::string> tokens = token(user_input);
    


    if (user_input.empty()) {
        continue;
    }
    bool check = error(tokens.at(0));

    if(check == false){
    
    echo(tokens);
    type(tokens);
    }

    if(!tokens.empty()&&tokens.at(0) == "exit"){
        break;  
    }
  }


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


//echo command
void echo(std::vector<std::string> tokens){
    if(tokens.at(0) == "echo"){
        for(int i=1;i<tokens.size();i++){
            std::cout << tokens[i]<< " ";
        }
        std::cout << "\n";
    }
}

//worng command 
bool error(std::string user_input){
    if(valid_command.count(user_input) != 1){
        std::cout<<user_input<< " :command is not valid\n";
        return true;
    }
    else{
        return false;
    }
}

void type(std::vector<std::string> tokens){
    if(tokens.at(0) == "type"){
        std::cout << tokens.at(1) << " is a shell builtin\n";
    }
}