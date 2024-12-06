
CXX := g++

EXECUTABLE ?= stratego

SRC_DIR ?= Code
BLD_DIR ?= build
INC_DIR := $(shell find $(SRC_DIR) -type d)

SRCS := $(shell find $(SRC_DIR) -name *.cpp)
OBJS := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS := $(OCJS:.o=.d)

LDFLAGS := -lncurses -L external_libraries/ASCII_Board_Game_Engine_v1.4.1-alpha/Linux/ -lascii_engine
INC_FLAGS := $(addprefix -I,$(INC_DIR))
CXXFLAGS := -std=c++17 -O2 $(INC_FLAGS) -Wall -MMD -MP -I external_libraries/ASCII_Board_Game_Engine_v1.4.1-alpha/Linux/headers/ascii_engine

.PHONY: all clean

OUT := stratego

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	mkdir $(BLD_DIR)/bin
	mv stratego $(BLD_DIR)/bin
	cp external_libraries/ASCII_Board_Game_Engine_v1.4.1-alpha/Linux/libascii_engine.so $(BLD_DIR)/bin
	cp -r board_configs $(BLD_DIR)/bin
	rm -rf $(BLD_DIR)/Code
	cp Stratego.sh $(BLD_DIR)

$(BLD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -r $(BLD_DIR)

-include $(DEPS)
