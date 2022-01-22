#include <ncurses.h>
#include <stdlib.h>

void render(int *board, int width, int height) {
    int i;
    for (i=0; i<width*height; i++) {
        addch(board[i] == 0 ? ' ' : '#');

        /* change line when the index reaches the multiple of the width */
        if ((i + 1) % width == 0) {
            addch('\n');
        }
    }

}

int main(void) {
    int width = 3;
    int height = 3;

    /* process the board as an 1D array */
    int board[] = {
        0, 1, 1,
        1, 0, 1,
        0, 0, 1
    };

    initscr();

    render(board, width, height);

    refresh();

    addstr("\n\n\n\npress any key to contiune...");
    refresh();

    getch();
    endwin();

    return EXIT_SUCCESS;
}
