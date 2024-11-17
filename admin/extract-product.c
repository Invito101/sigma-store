#include "../headers.h"
#include <stdio.h>
#include <sqlite3.h>
#include <ncurses.h>



int callback(void *data, int argc, char **argv, char **azColName) {
    mvprintw(0, 0, "%s:", (const char *)data);
    for (int i = 0; i < argc; i++) {
        attron(COLOR_PAIR(1));
        mvprintw(i + 2, 0, "%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
        attroff(COLOR_PAIR(1));
    }
    refresh();
    return 0;
}

int call(char *name) {
    sqlite3 *db;
    char *err_msg2 = 0;
    int rc;
    // mvprintw(0, 1, "call called");
    // refresh();

    rc = sqlite3_open("db/SigmaStore.db", &db);
    if (rc != SQLITE_OK) {
        mvprintw(1, 1, "Cannot open database: %s", sqlite3_errmsg(db));
        refresh();
        return -1;
    }

    // mvprintw(2, 1, "Database opened successfully");
    // refresh();

    char sql[200];
    snprintf(sql, sizeof(sql), "SELECT * FROM Products WHERE name='%s';", name);
    const char *data = "Product Information";

    rc = sqlite3_exec(db, sql, callback, (void *)data, &err_msg2);
    if (rc != SQLITE_OK) {
        mvprintw(3, 1, "SQL Error: %s", err_msg2);
        refresh();
        sqlite3_free(err_msg2);
    } 

    sqlite3_close(db);
    // mvprintw(5, 1, "Database closed");
    // refresh();
    return 0;
}
