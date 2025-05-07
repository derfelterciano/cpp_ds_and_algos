# Makefile

# Compiler settings
CXX       := clang++
CXXFLAGS  := -std=c++17 -Wall -Wextra -Iheaders -Isrc
LDFLAGS   :=

# Directories
SRC_DIR   := src
TEST_DIR  := tests

# Sources
APP_SRC   := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRC  := $(wildcard $(TEST_DIR)/*.cpp)

# Objects
APP_OBJS  := $(APP_SRC:.cpp=.o)
TEST_OBJS := $(TEST_SRC:.cpp=.o)

# Targets
APP_BIN     := app
TEST_BIN    := test_linkedlist

.PHONY: all app test clean

all: app test

# Build the main application from src/*.cpp
app: $(APP_BIN)

$(APP_BIN): $(APP_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Build the test executable from tests/*.cpp
test: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# Generic rule to compile any .cpp → .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(APP_OBJS) $(TEST_OBJS) $(APP_BIN) $(TEST_BIN)

