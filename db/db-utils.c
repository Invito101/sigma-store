#include <stdio.h>
#include <sqlite3.h>
#include "../headers.h"

sqlite3* open_db(void){
    sqlite3 *db;
    int rc = sqlite3_open("db/SigmaStore.db", &db);

    if (rc != SQLITE_OK){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Close the database connection if it was partially opened
        exit(0);
    }

    return db;
}

int create_tables(void){
    sqlite3 *db = open_db();
    char *errMsg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300) UNIQUE, role VARCHAR(10), password VARCHAR(110), phoneNumber VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, createdAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP);"
    "CREATE TABLE IF NOT EXISTS Products(id INTEGER PRIMARY KEY, );";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Failed to create tables: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}