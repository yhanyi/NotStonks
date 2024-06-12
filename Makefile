# Makefile

CXX = g++
CXXFLAGS = -std=c++17
SRCS = main.cpp $(wildcard trade/*.cpp) $(wildcard ml/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TMPFILES = $(wildcard trade/*.tmp) $(wildcard ml/*.tmp)
CSVFILES = $(wildcard datasets/finance/*.csv)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET) $(TMPFILES) $(CSVFILES)