#include <stdio.h>
#include <sqlite3.h>

sqlite3* open_db(void){
    sqlite3 *db;
    int rc = sqlite3_open("db/SigmaStore.db", &db);

    if (rc != SQLITE_OK){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Close the database connection if it was partially opened
        return NULL;
    }

    printf("Database opened (or created) successfully.\n");
    sqlite3_close(db);
    return db;
}

int create_tables(void){
    sqlite3 *db = open_db();
    if(db == NULL) return 1;
    char *errMsg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300), role VARCHAR(10), password TEXT, phone_number VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL Error: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

