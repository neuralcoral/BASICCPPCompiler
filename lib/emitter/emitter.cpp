//
// Created by George Alfaro on 12/26/24.
//

#include "emitter.h"

#include <fstream>


Emitter::Emitter(const std::string& outputFile) {
    filePath = outputFile;
    header = "";
    code = "";
}

void Emitter::emit(const std::string& code) {
    this->code += code;
}

void Emitter::emitLine(const std::string& code) {
    this->code += code + '\n';
}

void Emitter::headerLine(const std::string& code) {
    this->header += code + '\n';
}

void Emitter::writeFile() const {
    std::ofstream file(filePath);
    file << this->header << this->code;
    file.close();
}
