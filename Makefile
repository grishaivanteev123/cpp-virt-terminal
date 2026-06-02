CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = virtual_terminal

all: $(TARGET)

$(TARGET): Terminal.cpp Directory.cpp SingleLineFile.cpp MultiLineFile.cpp Entry.cpp
	$(CXX) $(CXXFLAGS) Terminal.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)