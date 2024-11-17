#include "../../headers.h"

int create_product(char *name, int price, char *description, char *category, char *manufacturedBy){
    sqlite3 *db = open_db();
    char *errMsg = 0;

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO Products(name, price, description, category, manufacturedBy, rating, noOfRatings, amountBought) VALUES(?,?,?,?,?,0,0,0);";

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
    sqlite3_bind_text(stmt, 4, category, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, manufacturedBy, -1, SQLITE_STATIC);

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

int modify_product(char *name, char *new_name, int new_price, char *new_description, char *new_category, char *new_manufacturedBy){
    sqlite3* db = open_db();
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Products SET name = ?, price = ?, description = ?, category = ?, manufacturedBy = ? WHERE name = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, new_name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, new_price);
    sqlite3_bind_text(stmt, 3, new_description, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, new_category, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, new_manufacturedBy, -1, SQLITE_STATIC);

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

int productDataCallback(void *productWrapper, int argc, char **argv, char **azColName) {
    ProductArrayWrapper *wrapper = (ProductArrayWrapper *)productWrapper;
    Product *productObject = &wrapper->products[wrapper->currentIndex];

    cast_row_to_product_struct(productObject, argv);

    wrapper->currentIndex++;
    return 0;
}

Product* get_all_products(int *size){
    sqlite3 *db = open_db();
    
    char *errMsg = 0;
    int count = count_all_products();
    if (count <= 0) {
        *size = 0;
        sqlite3_close(db);
        return NULL;
    }

    Product *products = malloc(count * sizeof(User));
    if (!products) {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        sqlite3_close(db);
        return NULL;
    }

    ProductArrayWrapper wrapper = { .products = products, .currentIndex = 0 };

    char *sql = "SELECT * FROM Products";
    int rc = sqlite3_exec(db, sql, productDataCallback, &wrapper, &errMsg);

    if (rc != SQLITE_OK){
        fprintf(stderr, "%s: Execution of Query : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        free(products);
        return NULL;
    }

    sqlite3_close(db);
    *size = count;
    return products;
}

Product* get_all_category_products(int *size, char *cName){
    sqlite3 *db = open_db();

    char *errMsg = 0;
    int count = count_all_category_products(cName);
    if (count <= 0) {
        *size = 0;
        sqlite3_close(db);
        return NULL;
    }

    Product *products = malloc(count * sizeof(User));
    if (!products) {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        sqlite3_close(db);
        return NULL;
    }

    ProductArrayWrapper wrapper = { .products = products, .currentIndex = 0 };

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Products WHERE category = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, cName, -1, SQLITE_STATIC);

    while(sqlite3_step(stmt) == SQLITE_ROW){
        Product *productObject = &(wrapper.products[wrapper.currentIndex]);

        char *values[10];
        for (int i = 0; i < 10; i++){
            values[i] = (char *)sqlite3_column_text(stmt, i);
        }

        cast_row_to_product_struct(productObject, values);

        wrapper.currentIndex++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    *size = count;
    return products;
}