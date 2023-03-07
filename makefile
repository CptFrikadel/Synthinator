
CXX := g++

EXE := synth

CFLAGS := -std=c++20 -Wall -Wextra -g

SRC_DIR := src
OBJ_DIR := bin

SRC := $(wildcard $(SRC_DIR)/*.cpp)

OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

LDFLAGS :=  -lasound -pthread

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR):
	mkdir $@

clean:
	$(RM) -r $(OBJ_DIR)

.PHONY: all clean
