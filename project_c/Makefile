FLAGS= -std=c99 -Wall -o2
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
INCLUDES=includes
SRC=src
OBJ=obj

all: main interpretador show reviews user business structs reading sgr all program

program: $(wildcard $(SRC)/*.c)
	$(COMPILER) $(FLAGS) $(wildcard $(SRC)/*.c) $(PKG)  -o program 

clean: 
	rm program


