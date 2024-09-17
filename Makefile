CC = gcc
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lm
INC = butao.c tinyexpr.c

all:
	$(CC) main.c $(INC) $(LIBS)

run: all
	./a.out > saida.log