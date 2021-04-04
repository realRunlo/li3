FLAGS= -std=c99 -Wextra -arch arm64  -O2 -D_GNU_SOURCE 
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
INCLUDES=includes
SRC=src
OBJ=obj

all: main reviews user business structs reading sgr allprog
	
prog: $(SRC)/main.c $(SRC)/reviews.c $(SRC)/structs.c $(SRC)/reading.c $(SRC)/user.c $(SRC)/sgr.c  $(SRC)/business.c 
	$(COMPILER) $(FLAGS) -o exe $(SRC)/main.c $(SRC)/reviews.c $(SRC)/structs.c $(SRC)/reading.c $(SRC)/user.c $(SRC)/sgr.c  $(SRC)/business.c $(PKG)  


