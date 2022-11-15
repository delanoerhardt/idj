CPP        = g++
SRCS       = $(shell find src -name *.cpp)
OBJ        = $(addprefix $(DEST)/obj/,$(SRCS:%.cpp=%.o)) 
DIR        = $(addprefix $(DEST)/obj/,$(shell find src/ -type d)) 
DEST       = target
BIN        = $(DEST)/game.exe
RM         = rm -rf
CPP_FLAGS  = -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Iheaders -Wall -Wextra -g

LOG_DIR    = $(DEST)/logs
RUN_FLAGS   = > $(LOG_DIR)/latest.log 2>&1 & disown


.PHONY: all all-before clean run

all: all-before $(BIN)

all-before: 
	mkdir -p $(DEST) $(DIR) $(LOG_DIR)

clean:
	${RM} $(OBJ) $(BIN) $(DEST)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(CPP_FLAGS)

$(DEST)/obj/%.o: %.cpp
	$(CPP) -c $< -o $@ $(CPP_FLAGS)

run: all
	./$(BIN) $(RUN_FLAGS)