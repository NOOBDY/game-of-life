CC = clang
CFLAGS = -g -std=c89 -pedantic -Wall -O2
LDFLAGS = -lncursesw

game-of-life: game-of-life.c
	$(CC) game-of-life.c $(CFLAGS) $(LDFLAGS) -o game-of-life

clean:
	rm game-of-life

