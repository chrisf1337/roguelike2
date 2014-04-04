CC=clang++
DEBUG=-g
CFLAGS=-Wall $(DEBUG) -c
LFLAGS =-Wall $(DEBUG) -lncurses
OBJS = worldview.o world.o player.o creature.o

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

world.o: world.h world.cpp
	$(CC) $(CFLAGS) world.cpp

player.o: player.h player.cpp creature.h creature.cpp
	$(CC) $(CFLAGS) player.cpp

creature.o: creature.h creature.cpp world.h world.cpp
	$(CC) $(CFLAGS) creature.cpp


worldview.o: player.h world.h creature.h player.cpp world.cpp creature.cpp worldview.cpp
	$(CC) $(CFLAGS) worldview.cpp

clean:
	rm -rf *.o main main.dSYM
