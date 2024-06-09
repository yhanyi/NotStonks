# Makefile

CXX = g++
CXXFLAGS = -std=c++17
SRCS = \
main.cpp \
src/FinancialData.cpp \
src/Analysis.cpp \
src/MonteCarlo.cpp \
src/PortfolioOptimization.cpp \
src/TechnicalIndicators.cpp \
src/RiskMetrics.cpp \
src/Backtesting.cpp \
src/BlackScholes.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)