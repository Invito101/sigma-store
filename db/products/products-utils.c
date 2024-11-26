#include "../../headers.h"

int is_product_name_taken(char *name){
    sqlite3* db = open_db();
    sqlite3_stmt *stmt;

    char *sql = "SELECT COUNT(*) FROM Products WHERE name = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW){
        if(sqlite3_column_int(stmt, 0) == 0){
            sqlite3_finalize(stmt);
            close_db(db);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    close_db(db);
    return 1;
}

int get_product_no_of_rating(char *name){
    sqlite3* db = open_db();
    int noOfRating = 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT noOfRatings FROM Products WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        noOfRating = atoi((const char*)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    close_db(db);
    return noOfRating;
}

int count_all_products(){
    sqlite3 *db = open_db();

    char *sql = "SELECT COUNT(*) FROM Products;";
    int count = 0;
    char *errMsg = 0;

    if (sqlite3_exec(db, sql, countCallback, &count, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to count products: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    close_db(db);

    return count;
}

int count_all_category_products(char *cName){
    int count = 0;
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM Products WHERE category = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, cName, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        count = atoi((const char*)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return count;
}

double get_product_rating(char *name){
    sqlite3* db = open_db();
    double rating = 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT rating FROM Products WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        rating = atof((const char*)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    close_db(db);
    return rating;
}

int increase_amount_bought_by_one(char *name){
    sqlite3* db = open_db();

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET amountBought = amountBought + 1 WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    sqlite3_finalize(stmt);
    close_db(db);
    return 0;
}

int increase_no_of_ratings_by_one(char *name){
    sqlite3* db = open_db();

    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET noOfRatings = noOfRatings + 1 WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    close_db(db);
    return 0;
}

void cast_row_to_product_struct(Product *productObject, char **values){
    productObject->id = atoi(values[0]);

    if (values[1]) {
        strncpy(productObject->name, values[1], sizeof(productObject->name) - 1);
        productObject->name[sizeof(productObject->name) - 1] = '\0';
    }

    productObject->price = atoi(values[2]);

    if (values[3]) {
        strncpy(productObject->description, values[3], sizeof(productObject->description) - 1);
        productObject->description[sizeof(productObject->description) - 1] = '\0';
    }

    if (values[4]) {
        strncpy(productObject->category, values[4], sizeof(productObject->category) - 1);
        productObject->category[sizeof(productObject->category) - 1] = '\0';
    }

    if (values[5]) {
        strncpy(productObject->manufacturedBy, values[5], sizeof(productObject->manufacturedBy) - 1);
        productObject->manufacturedBy[sizeof(productObject->manufacturedBy) - 1] = '\0';
    }

    productObject->rating = atof(values[6]);

    productObject->noOfRatings = atoi(values[7]);

    productObject->amountBought = atoi(values[8]);

    productObject->createdAt = atoi(values[9]);
}