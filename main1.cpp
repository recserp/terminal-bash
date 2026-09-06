#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <span>
#include <iterator>

//command
std::vector<std::string> token(std::string user_input);

//function decalration
using CommandFn = std::function<void(std::vector<std::string>&)>;
void echo(const std::vector<std::string> &tokens);
void type(std::vector<std::string>& tokens,const std::unordered_map<std::string, CommandFn>& valid_command);
std::string get_env_var( std::string const & key );

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
void type(std::vector<std::string>& tokens,const std::unordered_map<std::string, CommandFn>& valid_command) {
        if (tokens.size() < 2) {
            std::cout << "type: missing argument, enter a command name after type\n";
            return;
        }
    for(std::size_t i=1;i<tokens.size();i++){
        if (valid_command.count(tokens[i])) {
            std::cout << tokens[i]<< " is a shell builtin\n";
        }
        else{
            std::string retval;
            retval = get_env_var();
            if(retval.length() != 0){
                std::cout << tokens[0] << " :"<< retval;
            }

            else{
            std::cout << tokens[i] << ": not found\n";
            }
        }
        
    }
}

//to search path
std::string get_env_var( std::string const & key ) {                                 
    char * val;                                                                        
    val = getenv( key.c_str() );                                                       
    std::string retval = "";                                                           
    if (val != NULL) {                                                                 
        retval = val;                                                                    
    }                                                                                  
    return retval;                                                                        
}         

