CC=clang++
DEBUG=-g
CFLAGS=-Wall $(DEBUG) -c
LFLAGS =-Wall $(DEBUG) -lncurses
OBJS = world.o player.o creature.o monster.o worldview.o

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

world.o: world.h world.cpp creature.h creature.cpp
	$(CC) $(CFLAGS) world.cpp

player.o: player.h player.cpp creature.h creature.cpp world.h world.cpp
	$(CC) $(CFLAGS) player.cpp

creature.o: creature.h creature.cpp world.h world.cpp
	$(CC) $(CFLAGS) creature.cpp

monster.o: monster.h monster.cpp creature.h creature.cpp world.h world.cpp
	$(CC) $(CFLAGS) monster.cpp

worldview.o: player.h world.h creature.h player.cpp world.cpp creature.cpp worldview.cpp
	$(CC) $(CFLAGS) worldview.cpp

clean:
	rm -rf *.o main main.dSYM
