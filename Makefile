CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -O2
OBJECTS = main.o lexer.o token_type.o token.o
TARGET = main
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)
main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
token_type.o: lib/token/token_type.cpp
	$(CXX) $(CXXFLAGS) -c token_type.cpp -o token_type.o
token.o: lib/token/token.cpp
	$(CXX) $(CXXFLAGS) -c token.cpp -o token.o
lexer.o: lib/lexer/lexer.cpp
	$(CXX) $(CXXFLAGS) -c lexer.cpp -o lexer.o
clean:
	rm -f $(TARGET) $(OBJECTS)