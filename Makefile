CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SOURCES = Terminal.cpp Entry.cpp Directory.cpp SingleLineFile.cpp MultiLineFile.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = virtual_terminal

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)