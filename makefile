CC = g++

OBJ_DIR = obj
SRC_DIR = src

OBJS = $(OBJ_DIR)/game.o \
	   $(OBJ_DIR)/Motor.o

	   
LDFLAGS = -lSDL3 -lm
CFLAGS = -g -Wall

all: clean game
# all: game

game: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o game $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -r $(OBJ_DIR)