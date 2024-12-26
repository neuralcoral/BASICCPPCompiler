//
// Created by George Alfaro on 12/17/24.
//
#include <iostream>
#include <__filesystem/operations.h>

#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>

#include "emitter.h"

std::string read_file(const std::string& file_name);

int main(int argc, char* argv[]) {

  const auto source = read_file(argv[1]);
  std::string outputFileName;
  if (argc < 3) {
    outputFileName = std::string(argv[1]) + ".c";
  } else {
    outputFileName = std::string(argv[2]);
  }
  auto lexer = Lexer(source);
  auto emitter = Emitter(outputFileName);
  auto parser = Parser(&lexer, &emitter);

  parser.program();
  emitter.writeFile();

  std::cout << "Compiling completed. See '" << outputFileName << "'\n";
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