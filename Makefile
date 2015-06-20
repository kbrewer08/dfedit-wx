CC := g++
EXE := wxDFedit
EXE_DIR := bin/
EXE_PATH := $(EXE_DIR)$(EXE)
OBJ_LIST = interface/DFTab.o interface/GeneralsTab.o interface/wxDFeditApp.o interface/wxDFeditMain.o
OBJ_DIR := obj/
OBJS = $(foreach obj,$(OBJ_LIST), $(OBJ_DIR)$(obj))
LIBS = $(shell wx-config --libs base, core, aui)
CXXFLAGS = -Wall -O2 -s $(shell wx-config --cflags)

build: $(EXE_PATH)

$(EXE_PATH): $(OBJS)
	$(CC) -s -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJS) $(EXE_PATH)

rebuild: clean build
