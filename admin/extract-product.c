#include "../headers.h"
#include <stdio.h>
#include <sqlite3.h>
#include <ncurses.h>



int callback(void *data, int argc, char **argv, char **azColName) {
    mvprintw(10, 0, "%s:", (const char *)data);
    for (int i = 0; i < argc; i++) {
        const char *col_name = azColName[i];          // Column name
        const char *col_value = argv[i] ? argv[i] : "NULL";  // Column value, handling NULLs

        attron(COLOR_PAIR(1));
        mvprintw(i + 12, 0, "%s = %s", azColName[i], argv[i] ? argv[i] : "NULL");
        attroff(COLOR_PAIR(1));
    }
    refresh();
    return 0;
}

int call(char *name) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
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

    const char *data = "Product Information";
    // Prepare the SQL query
    const char *sql = "SELECT * FROM Products WHERE name = ?;";

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);  // Bind name to the first placeholder
// Execute the prepared statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int argc = sqlite3_column_count(stmt); 
        const char *argv[argc]; 
        const char *azColName[argc]; 
        for (int i = 0; i < argc; i++) 
        { argv[i] = (const char *)sqlite3_column_text(stmt, i);
         azColName[i] = sqlite3_column_name(stmt, i); 
        } 
        callback((void *)data, argc, (char **)argv, (char **)azColName); 
        } 
    else if (rc == SQLITE_DONE) {
        mvprintw(3, 1, "No matching product found.");
        refresh();
    } else {
        mvprintw(3, 1, "Execution failed: %s", sqlite3_errmsg(db));
        refresh();
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    // mvprintw(5, 1, "Database closed");
    // refresh();
    return 0;
}
