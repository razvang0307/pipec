SRC = pipe.c
OBJ = ${SRC:.c=.o}
CC = gcc
CFLAGS = -g -Wall -Werror
LDFLAGS = -lncursesw

build: pipec

${OBJ}:

pipec: ${OBJ}
	${CC} ${CFLAGS} -o pipec $? ${LDFLAGS}

clean:
	rm pipec pipe.o
