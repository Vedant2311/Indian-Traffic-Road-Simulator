CXX = g++
CXXFLAGS = -I -g

output: open.o Parser.o 
	$(CXX) $(CXXFLAGS) -o output open.o Parser.o -lglut -lGLU -lGL -std=c++11

open.o: open.cpp
	$(CXX) -c open.cpp

Parser.o: Parser.cpp
	$(CXX) -c -std=c++11 Parser.cpp

clean:
	rm *.o output
