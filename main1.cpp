#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include "stdc++.h"


std::vector<std::string> token(std::string user_input);
void echo(std::vector<std::string> tokens);
bool error(std::string user_input);
void type(std::vector<std::string> tokens,std::string user_input);

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
    


    if (tokens.empty()) {
        continue;
    }
    bool check = error(tokens.at(0));

    
    if(!tokens.empty()&&tokens.at(0) == "exit"){
        break;  
    }
    if(check == false){
    
    echo(tokens);
    type(tokens,user_input);
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
void echo(std::vector<std::string> tokens) {
    // 1. Guard against size 0 (Prevents throw.cpp completely)
    if (tokens.empty()) {
        std::cout << "no characters entered after echo\n";
        return;
    }

    // 2. Safely check command name
    if (tokens[0] == "echo") {
        if (tokens.size() == 1) {
            std::cout << "no characters entered after echo\n";
            return;
        }

        for (std::size_t i = 1; i < tokens.size(); i++) {
            std::cout << tokens[i] << " \n";
        }
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


//fix the type function 
void type(std::vector<std::string> tokens,std::string user_input){
    if(tokens.size()<2 && tokens.at(0) == "type"){
        std::cout << " :command missing enter a command name after type \n";

    }
    else{
    auto temp = valid_command.find(tokens.at(1));
while(tokens[0] == "type"){
    if(temp !=valid_command.end()){
        std::cout <<tokens[1]<< " is a builtin\n";
        break;
    }
    else{
        std::cout <<tokens[1]<<" is not a builtin\n";
        break;
    }
}
    }
}