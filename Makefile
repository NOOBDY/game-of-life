game-of-life: game-of-life.c
	gcc game-of-life.c -std=c89 -pedantic -lncursesw -o game-of-life

clean:
	rm game-of-life

