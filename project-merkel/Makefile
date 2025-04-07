# Makefile for MerkelMain project

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.

# Source files
SRCS := main.cpp MerkelMain.cpp OrderBook.cpp OrderBookEntry.cpp CSVReader.cpp Wallet.cpp
OBJS := $(SRCS:.cpp=.o)

# Output binary
TARGET := main

# Default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
