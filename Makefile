SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

CPPFLAGS := -std=c++14 -Iinclude -MP -MMD -Wall -Wextra #-Werror -Wconversion

all: CPPFLAGS += -O2
debug: CPPFLAGS += -DDEBUG -Og -g -fno-access-control

.PHONY: all clean clena debug

EXE := $(BIN_DIR)/sim

DEBUG := $(BIN_DIR)/debug

SRC := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

$(info Found source files $(SRC))

OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

$(info OBJ is $(OBJ))

DEBUG_OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.debug.o, $(SRC))

all: $(EXE)

sim: $(EXE)

parallel: $(EXE)

debug: $(DEBUG)

# I make this typo constantly
clena: clean

clean:
	@$(RM) -rv $(OBJ_DIR) $(BIN_DIR)
	@$(RM) -rv ./*.o

$(DEBUG): $(DEBUG_OBJ) | $(BIN_DIR)
	$(CXX) $^ $(LDFLAGS) -o $@

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(ROOTS)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.debug.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(ROOTS)
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@ $@/component $@/simulation $@/graphics $@/cli $@/physics $@/graphics $@/util $@/demo

$(BIN_DIR):
	mkdir -p $@