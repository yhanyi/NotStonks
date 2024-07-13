# Makefile

CXX = g++
CXXFLAGS = -std=c++17
SRCS = \
main.cpp \
$(wildcard src/*.cpp) \
# $(wildcard src/mlcpp/*.cpp)
OBJS = $(SRCS:.cpp=.o)
TMPFILES = \
$(wildcard src/*.tmp) \
# $(wildcard src/mlcpp/*.tmp)
CSVFILES = $(wildcard datasets/finance/*.csv)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET) $(TMPFILES) $(CSVFILES)