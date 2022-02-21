#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include <ncurses.h>


struct Board {
    int width;
    int height;

    int *values;
};

void init(struct Board *board, const char *path) {
    FILE *file = fopen(path, "r");
    int i = 0, ch = 0, size = 0, width = 0, height = 0;

    while (ch != EOF) {
        ch = fgetc(file);

        if (ch == '\n') {
            height++;
            continue;
        }

        size++;
    }

    width = size / height;

    if (size - 1 != width * height) {
        printf("Wrong board dimensions\n");
        exit(1);
    }

    board->width = width;
    board->height = height;
    board->values = realloc(board->values, width * height * sizeof(int));

    if (!board->values) {
        printf("Failed to initialize\n");
        exit(1);
    }


    rewind(file);
    ch = 0;
    i = 0;

    while (ch != EOF) {
        ch = fgetc(file);

        if (ch == '\n')
            continue;

        board->values[i] = ch == '0' ? 0 : 1;
        ++i;
    }

    fclose(file);

}

void render(const struct Board *board) {
    int i;

    curs_set(0);

    for (i = 0; i < board->width * board->height; i++)
        mvaddstr(i / board->width, i % board->width * 2, board->values[i] ? "██" : "░░" );

}

void update(struct Board *board) {
    /* just for alias purposes */
    const int width = board->width;
    const int height = board->height;

    int *new_values = malloc(width * height * sizeof(int));

    int i;
    for (i = 0; i < width * height; i++) {
        int left   = i % width == 0            ? 1 : 0;
        int right  = i % width == width - 1    ? 1 : 0;
        int top    = i < width                 ? 1 : 0;
        int bottom = i >= width * (height - 1) ? 1 : 0;

        int alive = 0;
        alive += board->values[i - width + top * width * height - 1 + left * width];
        alive += board->values[i - width + top * width * height];
        alive += board->values[i - width + top * width * height + 1 - right * width];
        alive += board->values[i - 1 + left * width];
        alive += board->values[i + 1 - right * width];
        alive += board->values[i + width - bottom * width * height - 1 + left * width];
        alive += board->values[i + width - bottom * width * height];
        alive += board->values[i + width - bottom * width * height + 1 - right * width];

        if (board->values[i] && (alive < 2 || alive > 3)) {
            new_values[i] = 0;
            continue;
        }

        if (!board->values[i] && alive == 3) {
            new_values[i] = 1;
            continue;
        }

        new_values[i] = board->values[i];

    }

    memcpy(board->values, new_values, width * height * sizeof(int));
    free(new_values);
}

int main(void) {
    /* process the board as an 1D array */
    struct Board init_values = {0, 0, NULL};
    struct Board *board = &init_values;
    init(board, "board.txt");

    setlocale(LC_ALL, ""); /* unicode setup */
    initscr(); /* this line must be in front of nodelay() for some reason */
    nodelay(stdscr, true); /* makes getch() non blocking */

    while (true) {
        int ch = getch();
        if (ch == 'q')
            break;

        render(board);
        update(board);
        napms(200);
    }

    free(board->values);
    endwin();
    return EXIT_SUCCESS;
}
