CPP      = g++
SRCS	   = $(shell find src -name *.cpp)
OBJ      = $(addprefix target/obj/,$(SRCS:%.cpp=%.o)) 
DIR      = $(addprefix target/obj/,$(shell find src/ -type d)) 
BIN      = target/game.exe
RM       = rm -rf
FLAGS    = -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

.PHONY: all all-before clean run

all: all-before $(BIN)

all-before: 
	mkdir -p target $(DIR)

clean:
	${RM} $(OBJ) $(BIN) target

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(FLAGS)

target/obj/%.o: %.cpp
	$(CPP) -c $< -o $@ $(FLAGS)

run: all
	./$(BIN)