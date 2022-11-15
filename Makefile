DEST       = target
SRCS       = $(shell find src -name *.cpp)
OBJ        = $(addprefix $(DEST)/obj/,$(SRCS:%.cpp=%.o)) 
DIR        = $(addprefix $(DEST)/obj/,$(shell find src/ -type d)) 
BIN        = $(DEST)/game.exe
CMD_RM     = rm -rf

GPP        = g++
GPP_INC    = -I/usr/include/SDL2 -Iheaders
GPP_WARNS  = -Wall -Wextra -Wno-unused
GPP_LIBS   = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

GPP_FLAGS   = $(GPP_INC) $(GPP_WARNS) $(GPP_LIBS)

LOG_DIR    = $(DEST)/logs
RUN_FLAGS   = > $(LOG_DIR)/latest.log 2>&1 & disown


.PHONY: all all-before clean run

all: all-before $(BIN)

all-before: 
	mkdir -p $(DEST) $(DIR) $(LOG_DIR)

clean:
	${CMD_RM} $(OBJ) $(BIN) $(DEST)

$(BIN): $(OBJ)
	$(GPP) $(OBJ) -o $(BIN) $(GPP_FLAGS)

$(DEST)/obj/%.o: %.cpp
	$(GPP) -c $< -o $@ $(GPP_FLAGS)

run: all
	./$(BIN) $(RUN_FLAGS)