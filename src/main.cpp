//
// Created by George Alfaro on 12/17/24.
//
#include <iostream>
#include <__filesystem/operations.h>

#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>

std::string read_file(const std::string& file_name);

int main(int argc, char* argv[]) {

  const auto source = read_file(argv[1]);
  auto lexer = Lexer(source);
  auto parser = Parser(&lexer);
  parser.program();

  std::cout << "Parser completed." << std::endl;
  return 0;
}

std::string read_file(const std::string& file_name) {
  if (file_name.empty()) {
    std::cerr << "File name cannot be empty." << std::endl;
    throw std::invalid_argument("File name cannot be empty.");
  }
  std::stringstream buffer;
  if (std::filesystem::exists(file_name)) {
    if (std::ifstream file(file_name); file.is_open()) {
      buffer << file.rdbuf();
    } else {
      std::cerr << "File could not be opened." << std::endl;
      throw std::runtime_error("File could not be opened.");
    }
  } else {
    std::cerr << "File done not exist." << std::endl;
    throw std::runtime_error("File does not exist.");
  }
  std::string fileContent = buffer.str();
  return fileContent;
}