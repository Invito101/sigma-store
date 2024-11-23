#include <ncurses.h>

void scr() {
    clear();
    // Create a pad of 1000 rows and 200 columns
    int pad_rows = 1000;
    int pad_cols = 200;
    WINDOW *pad = newpad(pad_rows, pad_cols);
    if (pad == NULL) {
        endwin();
        printf("Error creating pad.\n");
        return 1;
    }

    // Fill the pad with some content
    for (int i = 0; i < pad_rows; i++)  {
            mvwprintw(pad, i, 0, "%d", i); // Example content
        
    }

    // Display part of the pad on the screen
    int start_row = 0, start_col = 0;
    int display_rows = LINES < 40 ? LINES : 40;
    int display_cols = COLS < 50 ? COLS : 50;
    prefresh(pad, start_row, start_col, 0, 0, display_rows - 1, display_cols - 1);

    int ch;
    while ((ch = getch()) != 'q') { // Press 'q' to exit
        switch (ch) {
            case KEY_UP:
                if (start_row > 0) start_row--;
                break;
            case KEY_DOWN:
                if (start_row < pad_rows - display_rows) start_row++;
                break;
            case KEY_LEFT:
                if (start_col > 0) start_col--;
                break;
            case KEY_RIGHT:
                if (start_col < pad_cols - display_cols) start_col++;
                break;
        }
        prefresh(pad, start_row, start_col, 0, 0, display_rows - 1, display_cols - 1);
    }

    // Cleanup
    delwin(pad);
}

