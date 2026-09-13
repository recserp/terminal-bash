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
#include <filesystem>

//command
std::vector<std::string> token(std::string user_input);

//function decalration
using CommandFn = std::function<void(std::vector<std::string>&)>;
void echo(const std::vector<std::string> &tokens);
void type(std::vector<std::string>& tokens,const std::unordered_map<std::string, CommandFn>& valid_command);
std::string get_env_var( std::string const & key );
std::string resolve_executable_in_path(const std::string& command_name);
std::unordered_map<std::string, std::string> aliases;
std::unordered_set<std::string> keywords;
std::unordered_map<std::string, std::string> shell_functions;

//command map
std::unordered_map<std::string,CommandFn> valid_command ;


int main() {
  std::string user_input;
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
  bool running = true;

  aliases["ll"] = "ls -l";
  aliases["la"] = "ls -a";
  shell_functions["myfunc"] = "echo hello";
  keywords = {
      "if", "then", "else", "elif", "fi", "for", "while", "until", "do", "done",
      "case", "esac", "function", "select", "in", "time", "coproc"
  };

    valid_command["exit"] = [&running](std::vector<std::string>& tokens) {
    running = false;
    };
    valid_command["echo"] = echo;
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

    for (std::size_t i = 1; i < tokens.size(); ++i) {
        const std::string& name = tokens[i];

        if (aliases.count(name)) {
            std::cout << name << " is aliased to '" << aliases[name] << "'\n";
            continue;
        }

        if (valid_command.count(name)) {
            std::cout << name << " is a shell builtin\n";
            continue;
        }

        if (shell_functions.count(name)) {
            std::cout << name << " is a function\n";
            continue;
        }

        if (keywords.count(name)) {
            std::cout << name << " is a shell keyword\n";
            continue;
        }

        const std::string resolved = resolve_executable_in_path(name);
        if (!resolved.empty()) {
            std::cout << name << " is " << resolved << "\n";
            continue;
        }

        std::cout << name << ": not found\n";
    }
}

std::string resolve_executable_in_path(const std::string& command_name) {
    if (command_name.empty()) {
        return "";
    }

    std::filesystem::path command_path(command_name);
    if (command_path.is_absolute() || command_name.find('/') != std::string::npos || command_name.find('\\') != std::string::npos) {
        if (std::filesystem::exists(command_path) && std::filesystem::is_regular_file(command_path)) {
            return command_path.string();
        }
        return "";
    }

    const char* path_value = std::getenv("PATH");
    if (path_value == nullptr) {
        return "";
    }

    std::stringstream path_stream(path_value);
    std::string path_dir;
    while (std::getline(path_stream, path_dir, ';')) {
        if (path_dir.empty()) {
            continue;
        }

        const std::filesystem::path candidate = std::filesystem::path(path_dir) / command_name;
        if (std::filesystem::exists(candidate) && std::filesystem::is_regular_file(candidate)) {
            return candidate.string();
        }

        const char* path_ext = std::getenv("PATHEXT");
        if (path_ext != nullptr) {
            std::stringstream ext_stream(path_ext);
            std::string extension;
            while (std::getline(ext_stream, extension, ';')) {
                if (extension.empty()) {
                    continue;
                }

                const std::filesystem::path with_extension = std::filesystem::path(path_dir) / (command_name + extension);
                if (std::filesystem::exists(with_extension) && std::filesystem::is_regular_file(with_extension)) {
                    return with_extension.string();
                }
            }
        }
    }

    return "";
}

//to search path


