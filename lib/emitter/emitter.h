//
// Created by George Alfaro on 12/26/24.
//

#ifndef EMITTER_H
#define EMITTER_H
#include <string>


class Emitter {
    std::string filePath;
    std::string header;
    std::string code;

    public:
        explicit Emitter(const std::string& outputFile);
        void emit(const std::string& code);
        void emitLine(const std::string& code);
        void headerLine(const std::string& code);
        void writeFile() const;
};



#endif //EMITTER_H
