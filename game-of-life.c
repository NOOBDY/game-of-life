#include <locale.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void render(int *board, int width, int height) {
    int i;

    curs_set(0);

    for (i = 0; i < width * height; i++) {
        mvaddstr(i / width, i % width * 2, board[i] ? "██" : "  " );
    }
}

void update(int* board, int width, int height) {
    int *new_board = (int*)malloc(width * height * sizeof(int));
    int i;
    for (i = 0; i < width * height; i++) {
        int left   = i % width == 0           ? 1 : 0;
        int right  = i % width == width - 1   ? 1 : 0;
        int top    = i < width                ? 1 : 0;
        int bottom = i >= width * (height - 1) ? 1 : 0;

        int alive = 0;
        alive += board[i - width + top * width * height - 1 + left * width];
        alive += board[i - width + top * width * height];
        alive += board[i - width + top * width * height + 1 - right * width];
        alive += board[i - 1 + left * width];
        alive += board[i + 1 - right * width];
        alive += board[i + width - bottom * width * height - 1 + left * width];
        alive += board[i + width - bottom * width * height];
        alive += board[i + width - bottom * width * height + 1 - right * width];

        if (board[i] && (alive < 2 || alive > 3))
            new_board[i] = 0;

        else if (!board[i] && alive == 3)
            new_board[i] = 1;

        else
            new_board[i] = board[i];

    }

    memcpy(board, new_board, width * height * sizeof(int));
    free(new_board);
}

int main(void) {
    int width = 5;
    int height = 5;
    int init_values[] = {
        0,0,0,0,0,
        0,0,0,1,0,
        0,1,0,1,0,
        0,0,1,1,0,
        0,0,0,0,0
    };

    /* process the board as an 1D array */
    int *board = (int*)malloc(width * height * sizeof(int));
    memcpy(board, init_values, width * height * sizeof(int));
    setlocale(LC_ALL, "");
    initscr(); /* this line must be in front of nodelay() for some reason */
    nodelay(stdscr, true); /* makes getch() non blocking */

    render(board, width, height);

    while (true) {
        int ch = getch();
        if (ch != ERR) {
            free(board);
            endwin();
            return EXIT_SUCCESS;
        }
        update(board, width, height);
        render(board, width, height);
        napms(500);
    }

}
