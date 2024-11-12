#include <stdio.h>
#include <sqlite3.h>

int main(void) {
    sqlite3 *db;           
    int rc;                  

    rc = sqlite3_open("SigmaStore.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);     // Close the database connection if it was partially opened
        return 1;
    }

    printf("Database opened (or created) successfully.\n");
    sqlite3_close(db);
    return 0;
}
