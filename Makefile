CC = gcc
TARGET = main
SRCS =  \
main.c \
application/app.c \
card/card.c \
terminal/terminal.c \
server/server.c \



all:
		${CC} -o ${TARGET}.o ${SRCS} 

clean:
		rm -f *.bin *.hex *.o