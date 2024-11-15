#include "../../headers.h"

int is_product_name_taken(char *name){
    sqlite3* db = open_db();
    sqlite3_stmt *stmt;

    char *sql = "SELECT COUNT(*) FROM Products WHERE name = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW){
        if(sqlite3_column_text(stmt, 0) == 0){
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 1;
}

int get_product_no_of_rating(char *name){
    sqlite3* db = open_db();
    int noOfRating = 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT noOfRatings FROM Products WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        noOfRating = atoi(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return noOfRating;
}

double get_product_rating(char *name){
    sqlite3* db = open_db();
    double rating = 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT rating FROM Products WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        rating = atof(sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rating;
}

int increase_amount_bought_by_one(char *name){
    sqlite3* db = open_db();

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET amountBought = amountBought + 1 WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int increase_no_of_ratings_by_one(char *name){
    sqlite3* db = open_db();

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET noOfRatings = noOfRatings + 1 WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}