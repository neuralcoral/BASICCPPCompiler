//
// Created by George Alfaro on 12/17/24.
//
#include <iostream>
#include <__filesystem/operations.h>

#include "lexer.h"
#include "parser.h"
#include <fstream>

char* read_file(const char* file_name);

int main(int argc, char* argv[]) {

  const auto source = read_file(argv[1]);
  auto lexer = Lexer(source);
  auto parser = Parser(&lexer);

  auto token = lexer.getToken();
  while (token->tokenType != END_OF_FILE) {
    std::cout << toString(token->tokenType) << std::endl;
    delete token;
    token = lexer.getToken();
  }
  std::cout << "Parser completed." << std::endl;
  delete[] source;
  return 0;
}

char* read_file(const char* file_name) {
  if (file_name == nullptr) {
    std::cerr << "File name cannot be empty." << std::endl;
    throw std::invalid_argument("File name cannot be empty.");
  }
  char* fileContent;
  if (std::filesystem::exists(file_name)) {
    if (std::ifstream file(file_name); file.is_open()) {
      const unsigned int fileSize = std::filesystem::file_size(file_name);
      fileContent = new char[fileSize];
      file.read(fileContent, fileSize);
      file.close();
    } else {
      std::cerr << "File could not be opened." << std::endl;
      throw std::runtime_error("File could not be opened.");
    }
  } else {
    std::cerr << "File done not exist." << std::endl;
    throw std::runtime_error("File does not exist.");
  }
  return fileContent;
}