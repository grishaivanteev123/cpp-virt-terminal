CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = virtual_terminal

OBJS = main.o Directory.o SingleLineFile.o MultiLineFile.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

main.o: main.cpp Terminal.hpp Directory.hpp SingleLineFile.hpp MultiLineFile.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Directory.o: Directory.cpp Directory.hpp Entry.hpp
	$(CXX) $(CXXFLAGS) -c Directory.cpp

SingleLineFile.o: SingleLineFile.cpp SingleLineFile.hpp Entry.hpp
	$(CXX) $(CXXFLAGS) -c SingleLineFile.cpp

MultiLineFile.o: MultiLineFile.cpp MultiLineFile.hpp Entry.hpp
	$(CXX) $(CXXFLAGS) -c MultiLineFile.cpp

clean:
	rm -f $(OBJS) $(TARGET)