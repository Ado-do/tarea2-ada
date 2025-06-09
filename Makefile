# Compiler
CXX = g++

# Compiler flags
CXX_FLAGS = -Wall -Wextra -std=c++17 -ggdb

# Source files
SRCS = $(wildcard src/*.cpp)

# Compiled files
BINS = $(SRCS:src/%.cpp=build/%)


# Recipes
all: $(BINS)

build/%: src/%.cpp
	@mkdir -p build/
	$(CXX) $(CXX_FLAGS) -o $@ $<

clean:
	rm -rf build/

check:
	@echo "SRCS = $(SRCS)"
	@echo "BINS = $(BINS)"

.PHONY: all clean
