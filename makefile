CC = g++

OBJ_DIR = obj
SRC_DIR = src

IMGUI_DIR = src/imgui

OBJS = $(OBJ_DIR)/game.o \
	   $(OBJ_DIR)/Motor.o \
	   $(OBJ_DIR)/Vector.o \
	   $(OBJ_DIR)/Cubo.o \
	   $(OBJ_DIR)/Triangulo.o \
	   $(OBJ_DIR)/Malla.o

OBJS += $(IMGUI_DIR)/imgui.o \
		$(IMGUI_DIR)/imgui_demo.o \
		$(IMGUI_DIR)/imgui_draw.o \
		$(IMGUI_DIR)/imgui_tables.o \
		$(IMGUI_DIR)/imgui_widgets.o \
		$(IMGUI_DIR)/backends/imgui_impl_sdl3.o \
		$(IMGUI_DIR)/backends/imgui_impl_sdlrenderer3.o

LDFLAGS = -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -lSDL3 -lm
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