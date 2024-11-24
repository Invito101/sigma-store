#include "../../headers.h"

int add_item_to_cart(int userId, int quantity, int productId){
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO Cart(quantity, userId, productId) VALUES(?,?,?);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, quantity);
    sqlite3_bind_int(stmt, 2, userId);
    sqlite3_bind_int(stmt, 3, productId);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return 0;
}

int modify_item_in_cart(int userId, int quantity, int productId){
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;

    const char *sql = "UPDATE Cart SET quantity = ? WHERE userId = ? AND productId = ?";

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, quantity);
    sqlite3_bind_int(stmt, 2, userId);
    sqlite3_bind_int(stmt, 3, productId);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

int delete_cart_item(int userId, int productId){
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt;

    const char *sql = "DELETE FROM Cart WHERE userId = ? AND productId = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to prepare delete statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_int(stmt, 2, productId);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "%s : Failed to delete cart item: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

Cart* get_cart_items(int userId, int* size){
    sqlite3 *db = open_db();
    
    char *errMsg = 0;
    int count = count_cart_items_of_user(userId);
    if (count <= 0) {
        *size = 0;
        close_db(db);
        return NULL;
    }

    Cart *items = malloc(count * sizeof(Cart));
    if (!items) {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        close_db(db);
        return NULL;
    }

    CartArrayWrapper wrapper = { .items = items, .currentIndex = 0 };

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Cart WHERE orderId IS NULL AND userId = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, userId);

    while(sqlite3_step(stmt) == SQLITE_ROW){
        Cart *cartObject = &(wrapper.items[wrapper.currentIndex]);

        char *values[10];
        for (int i = 0; i < 10; i++){
            values[i] = (char *)sqlite3_column_text(stmt, i);
        }

        cast_row_to_cart_struct(cartObject, values);

        wrapper.currentIndex++;
    }

    close_db(db);
    *size = count;
    return items;
}

int mark_cart_as_ordered(int userId, int orderId){
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;

    const char *sql = "UPDATE Cart SET orderID = ? WHERE userId = ?;";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, orderId);
    sqlite3_bind_int(stmt, 2, userId);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return 0;
}