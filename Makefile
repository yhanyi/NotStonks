# Makefile

CXX = g++
CXXFLAGS = -std=c++17
SRCS = main.cpp $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TMPFILES = $(wildcard src/*.tmp)
CSVFILES = $(wildcard datasets/*.csv)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET) $(TMPFILES) $(CSVFILES)