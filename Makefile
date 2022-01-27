game-of-life: game-of-life.c
	gcc game-of-life.c -g -std=c89 -pedantic -lncursesw -Wall -o game-of-life

clean:
	rm game-of-life

