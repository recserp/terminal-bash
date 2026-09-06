#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include <functional>

//command
std::vector<std::string> token(std::string user_input);

//function decalration
using CommandFn = std::function<void(std::vector<std::string>&)>;
void echo(const std::vector<std::string> &tokens);
void type(std::vector<std::string>& tokens,const std::unordered_map<std::string, CommandFn>& valid_command);

//command map
std::unordered_map<std::string,CommandFn> valid_command ;

int main() {
  std::string user_input;
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  bool running = true;

    valid_command["exit"] = [&running](std::vector<std::string>& tokens) {
    running = false;
    };
    valid_command["echo"] = echo;                              
    valid_command["exit"] = [&running](std::vector<std::string>& tokens) { running = false; };
    valid_command["type"] = [](std::vector<std::string>& tokens) { type(tokens, valid_command); };



  while(running){
    std::cout << "$ ";
    std::getline(std::cin,user_input);
    std::vector<std::string> tokens = token(user_input);
    

    if (tokens.empty()) {
        continue;
    }

    auto it = valid_command.find(tokens[0]);
    if (it == valid_command.end()) {
        std::cout << tokens[0] << ": command not found\n";
            } 
    else {
        it->second(tokens); 
    }

  }

}


//tokens
std::vector<std::string> token(std::string user_input){
    std::vector<std::string> tokens;
    std::stringstream check1(user_input);
    std::string temp;
     while (check1 >> temp){
        
        tokens.push_back(temp);
    }
    return tokens;
}


//echo command
void echo(const std::vector<std::string>&tokens) {
        
    if (tokens.size() == 1) {
            std::cout << "no characters entered after echo\n";
            return;
        }

    if (tokens.size() >= 2 && tokens[0] == "echo"){
        for (std::size_t i = 1; i < tokens.size(); i++){
            std::cout<<tokens[i];
            if (i + 1 < tokens.size()) {
            std::cout << " "; 
                }
            }
        }
    std::cout << "\n";
}

//fixed the type function 
void type(std::vector<std::string>& tokens,const std::unordered_map<std::string, CommandFn>& commands) {
    if (tokens.size() < 2) {
        std::cout << "type: missing argument, enter a command name after type\n";
        return;
    }
    if (commands.count(tokens[1])) {
        std::cout << tokens[1] << " is a builtin\n";
    } else {
        std::cout << tokens[1] << " is not a builtin\n";
    }
}
