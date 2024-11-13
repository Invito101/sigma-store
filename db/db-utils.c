#include <stdio.h>
#include <sqlite3.h>
#include "../headers.h"

sqlite3* open_db(void){
    sqlite3 *db;
    int rc = sqlite3_open("db/SigmaStore.db", &db);

    if (rc != SQLITE_OK){
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); // Close the database connection if it was partially opened
        return NULL;
    }

    printf("Database opened (or created) successfully.\n");
    return db;
}

int create_tables(void){
    sqlite3 *db = open_db();
    if(db == NULL) return 1;
    char *errMsg = 0;

    char *sql = "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY, name VARCHAR(300), email VARCHAR(300) UNIQUE, role VARCHAR(10), password TEXT, phoneNumber VARCHAR(10), address VARCHAR(1000), pincode INT, state VARCHAR(100), money INT, createdAt TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";

    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    if(rc != SQLITE_OK){
        fprintf(stderr, "Failed to create tables: %s\n", errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int create_user(char *role, char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    sqlite3 *db = open_db();
    if(db == NULL) return 1;
    char *errMsg = 0;

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO USERS(name, email, role, password, phoneNumber, address, pincode, state, money) VALUES(?,?,?,?,?,?,?,?,?);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, role, -1, SQLITE_STATIC);
    // password encyption
    sqlite3_bind_text(stmt, 4, encrypt(password), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, phoneNumber, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, address, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, pincode);
    sqlite3_bind_text(stmt, 8, state, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, 0);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int create_customer(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Customer", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int create_seller(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Seller", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int create_admin(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Admin", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}