#include "../../headers.h"

int create_product(char *name, int price, char *description, char *manufacturedBy){
    sqlite3 *db = open_db();
    char *errMsg = 0;

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO Products(name, price, description, manufacturedBy, rating, noOfRatings, amountBought) VALUES(?,?,?,?,0,0,0);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, price);
    sqlite3_bind_text(stmt, 3, description, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, manufacturedBy, -1, SQLITE_STATIC);

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

int delete_product(char *name){
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt;

    const char *sql = "DELETE FROM Products WHERE name = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to prepare delete statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "%s : Failed to delete product: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int modify_product(char *name, char *new_name, int new_price, char *new_description, char *new_manufacturedBy){
    sqlite3* db = open_db();
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET name = ?, price = ?, description = ?, manufacturedBy = ? WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, new_price);
    sqlite3_bind_text(stmt, 3, new_description, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, new_manufacturedBy, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE){
        fprintf(stderr, "%s : Failed to update record: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int rate_product(char *name, int rating){
    sqlite3 *db = open_db();

    increase_no_of_ratings_by_one(name);
    int n = get_product_no_of_rating(name);
    double prevRating = get_product_rating(name);

    double newRating = ((prevRating * n) + rating) / (float) n;

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET rating = ? WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, newRating);
    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_STATIC);

    sqlite3_finalize(stmt);

    sqlite3_close(db);
    return 0;
}