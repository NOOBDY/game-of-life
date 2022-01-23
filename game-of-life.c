#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

void render(int *board, int width, int height) {
    int i;

    curs_set(0);

    for (i = 0; i < width * height; i++) {
        mvaddstr(i / height, i % width * 2, board[i] ? "██" : "  " );
    }
}

void update(int* board, int width, int height) {
    int i;
    for (i = 0; i < width * height; i++) {
        board[i] = !board[i];
    }
}

int main(void) {
    int width = 3;
    int height = 3;
    int init_values[] = {
        0, 1, 1,
        1, 0, 1,
        0, 0, 1
    };

    /* process the board as an 1D array */
    int *board = (int*)malloc(width * height);
    board = init_values;
    setlocale(LC_ALL, "");
    initscr(); /* this line must be in front of nodelay() for some reason */
    nodelay(stdscr, true); /* makes getch() non blocking */

    render(board, width, height);

    refresh();

    while (true) {
        int ch = getch();
        if (ch != ERR) {
            endwin();
            return EXIT_SUCCESS;
        }
        update(board, width, height);
        render(board, width, height);
        napms(1000);
    }

}
