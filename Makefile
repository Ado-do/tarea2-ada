# Compiler
CXX = g++

# Compiler flags
CXX_FLAGS = -Wall -Wextra -std=c++17

# Source files
SRCS = $(wildcard src/*)

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
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(BINS)

.PHONY: all clean
