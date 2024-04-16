CXX := clang
# CXX_FLAGS := -Wall -Wextra -ggdb

BIN	:= bin
SRC	:= src
INCLUDE	:=
LIB	:=
LIBRARIES	:= 
EXECUTABLE	:= proj_creator

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	@echo "🚧 Building..."
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	@echo "🧹 Clearing..."
	-rm $(BIN)/*

setup:
	@mkdir -p $(BIN) $(SRC) $(INCLUDE) $(LIB) $(LIBRARIES)
	@printf "%s\n" "#include <stdio.h>" "" "int main(void) {" "" "printf(\"Hello World!\n\");" "" "return 0;" "}" > $(SRC)/main.c
