# Makefile

CXX = g++
CXXFLAGS = -std=c++17
SRCS = main.cpp src/FinancialData.cpp src/Analysis.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)