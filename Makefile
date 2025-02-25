SRC = pipe.c
OBJ = ${SRC:.c=.o}
CC = gcc
CFLAGS = -g
LDFLAGS = -lncurses

build: pipec

${OBJ}:

pipec: ${OBJ}
	${CC} ${CFLAGS} -o pipec $? ${LDFLAGS}
