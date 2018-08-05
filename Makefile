.PHONY:ZTT_APP clean
CC=gcc
CFLAGS=-g -W -Wall
PWD=${shell pwd}
SOURCE_OBJ=./src/ZTT_Cmd.o ./src/ZTT_Main.o ./src/ZTT_music_main.o ./src/ZTT_ThreadPool.o ./src/ZTT_ThreadPoolTest.o
INCLUDE=-I ${PWD}/include
APP_LIB=-lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer
APP_LIB+=-lpthread

%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) -T default.lds $< -o $@
ZTT_APP:${SOURCE_OBJ}
	${CC} ${CFLAGS} ${INCLUDE} -T default.lds $^ -o $@ ${APP_LIB}

clean:
	rm ZTT_APP ${SOURCE_OBJ}
