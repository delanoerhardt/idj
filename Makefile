ifeq ($(OS),Windows_NT)
SHELL       = cmd.exe
SEP        := $(shell echo \)
else
SEP         = /
endif

DEST        = target

ifeq ($(OS),Windows_NT)
CUR_DIR			= $(shell echo %cd%)
SRC_FILES   = $(subst $(CUR_DIR)$(SEP),,$(shell dir .\src\*.cpp /S/B))

SRC_DIRS    = $(subst $(CUR_DIR)$(SEP),,$(shell dir .\src\* /S/B /A:D))
DIR         = $(addprefix $(DEST)$(SEP)obj$(SEP),$(SRC_DIRS))

OBJ         = $(addprefix $(DEST)/obj/,$(subst $(SEP),/,$(SRC_FILES:%.cpp=%.o))) 
else
SRC_FILES   = $(shell find src -name *.cpp)
DIR         = $(addprefix $(DEST)$(SEP)obj$(SEP),$(shell find src -type d))
OBJ         = $(addprefix $(DEST)/obj/,$(SRC_FILES:%.cpp=%.o)) 
endif
							
BIN         = $(DEST)$(SEP)game.exe


GPP         = g++
GPP_INC     = -I/usr/include/SDL2 -Iheaders
GPP_WARNS   = -Wall -Wextra -Wno-unused
GPP_LIBS    = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

GPP_FLAGS   = $(GPP_INC) $(GPP_WARNS) $(GPP_LIBS)

LOG_DIR     = $(DEST)$(SEP)logs
RUN_FLAGS   = > $(LOG_DIR)$(SEP)latest.log 2>&1 & disown

MKDIRS      = mkdir -p $(DEST)$(SEP) $(DIR) $(LOG_DIR)
RMDIRS      = rm -rf $(OBJ) $(BIN) $(DEST)


ifeq ($(OS),Windows_NT)

MKDIRS    = md $(DEST) $(DIR) $(LOG_DIR) > nul 2> nul & @
RMDIRS    = rd /S/Q $(DEST) > nul 2> nul & @

else
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf
endif
endif


.PHONY: all all-before clean run

all: all-before $(BIN)

all-before:
	$(MKDIRS)


clean:
	$(RMDIRS)

$(BIN): $(OBJ)
	$(GPP) $(OBJ) -o $(BIN) $(GPP_FLAGS)

$(DEST)/obj/%.o: %.cpp
	$(GPP) -c $< -o $@ $(GPP_FLAGS)

run: all
	./$(BIN) $(RUN_FLAGS)