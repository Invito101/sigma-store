#include <stdio.h>
#include <sqlite3.h>
#include "../headers.h"

sqlite3* open_db(void){
    sqlite3 *db;
    int rc = sqlite3_open("db/SigmaStore.db", &db);

    if (rc != SQLITE_OK){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        close_db(db); // Close the database connection if it was partially opened
        exit(0);
    }

    return db;
}

void close_db(sqlite3 *db){
    sqlite3_close(db);
}

int create_tables(void){
    sqlite3 *db = open_db();
    char *errMsg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300) UNIQUE, role VARCHAR(10), password VARCHAR(110), phoneNumber VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, createdAt INT NOT NULL);"

    "CREATE TABLE IF NOT EXISTS Products(id INTEGER PRIMARY KEY, name VARCHAR(300) UNIQUE, price INT, description VARCHAR(1000), category VARCHAR(300), manufacturedBy VARCHAR(300), rating DOUBLE, noOfRatings INT, amountBought INT, createdAt INT NOT NULL);"

    "CREATE TABLE IF NOT EXISTS Orders(id INTEGER PRIMARY KEY, userId INT, createdAt INT NOT NULL, delivered INT DEFAULT 0, FOREIGN KEY (userId) REFERENCES Users(id));"

    "CREATE TABLE IF NOT EXISTS Cart(id INTEGER PRIMARY KEY, quantity INT, userId INT, productId INT, orderId INT DEFAULT NULL, FOREIGN KEY (userId) REFERENCES Users(id), FOREIGN KEY (productId) REFERENCES Products(id), FOREIGN KEY (orderId) REFERENCES Orders(id));";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Failed to create tables: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        close_db(db);
        return -1;
    }

    close_db(db);
    return 0;
}