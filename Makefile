.PHONY:ZTT_APP clean
CC=gcc
CFLAGS=-g -W -Wall
PWD=${shell pwd}
SOURCE=${PWD}/src/*.c
INCLUDE=-I ${PWD}/include
APP_LIB=-lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
APP_LIB+=-lpthread

ZTT_APP:${SOURCE}
	${CC} ${CFLAGS} ${INCLUDE} $^ -o $@ ${APP_LIB}

clean:
	rm ZTT_APP *.o