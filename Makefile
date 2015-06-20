CC := g++
EXE := wxDFedit
EXE_DIR := bin/
EXE_PATH := $(EXE_DIR)$(EXE)
OBJ_LIST = DFTab.o GeneralsTab.o wxDFeditApp.o wxDFeditMain.o
OBJ_DIR := obj/
OBJS = $(foreach obj,$(OBJ_LIST), $(OBJ_DIR)$(obj))
LIBS = $(shell wx-config --libs core, base, aui)
CXXFLAGS = -Wall -O2 -s $(shell wx-config --version=3.0 --cflags)

build: $(EXE_PATH)

$(EXE_PATH): $(OBJS)
	$(CC) -s -o $@ $^ $(LIBS)

$(OBJ_DIR)%.o: interface/%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJS) $(EXE_PATH)

rebuild: clean build
