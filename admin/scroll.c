#include <ncurses.h>

int m() {
    initscr();
    noecho();
    cbreak();

    // Create a pad of 1000 rows and 200 columns
    int pad_rows = 1000;
    int pad_cols = 200;
    WINDOW *pad = newpad(pad_rows, pad_cols);

    // Fill the pad with some content
    for (int i = 0; i < pad_rows; i++) {
        for (int j = 0; j < pad_cols; j++) {
            mvwprintw(pad, i, j, "%c", 'A' + (j % 26)); // Example content
        }
    }

    // Display part of the pad on the screen
    int start_row = 0, start_col = 0;
    int display_rows = 20, display_cols = 50; // Size of the visible area

    // Refresh a portion of the pad to the screen
    prefresh(pad, start_row, start_col, 0, 0, display_rows - 1, display_cols - 1);

    getch(); // Wait for user input

    // Cleanup
    delwin(pad);
    endwin();
    return 0;
}
