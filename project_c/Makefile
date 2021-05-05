FLAGS= -std=c99 -Wextra -O2 -D_GNU_SOURCE 
PKG = `pkg-config --cflags --libs glib-2.0`
COMPILER=gcc
INCLUDES=includes
SRC=src
OBJ=obj

all: main interpretador show reviews user business structs reading sgr all program

valgrind:
	valgrind --leak-check=full \
		--show-leak-kinds=all \
         	--track-origins=yes \
         	--verbose \
         	--log-file=valgrind-out.txt \
		./allprog

program: $(SRC)/main.c $(SRC)/interpretador.c $(SRC)/show.c $(SRC)/reviews.c $(SRC)/structs.c $(SRC)/reading.c $(SRC)/user.c $(SRC)/sgr.c  $(SRC)/business.c $(SRC)/table.c 
	$(COMPILER) $(FLAGS) -o program $(SRC)/main.c $(SRC)/interpretador.c $(SRC)/show.c $(SRC)/reviews.c $(SRC)/structs.c $(SRC)/reading.c $(SRC)/user.c $(SRC)/sgr.c  $(SRC)/business.c $(SRC)/table.c $(PKG)  


