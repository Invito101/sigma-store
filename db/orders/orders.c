#include "../../headers.h"

int place_order(int userId){
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO Orders(createdAt, userId) VALUES(?,?);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, getISTTime());
    sqlite3_bind_int(stmt, 2, userId);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    int orderId = (int)sqlite3_last_insert_rowid(db);

    sqlite3_finalize(stmt);
    close_db(db);

    mark_cart_as_ordered(userId, orderId);
    return 0;
}

Order get_order(int orderId, int userId){
    sqlite3 *db = open_db();
    Order order = {0};

    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM Orders WHERE id = ?;";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return order;
    }

    sqlite3_bind_int(stmt, 1, orderId);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return order;
    }

    char *values[3];
    for (int i = 0; i < 3; i++){
        values[i] = (char *) sqlite3_column_text(stmt, i);
    }

    cast_row_to_order_struct(&order, values);

    order.items = get_cart_items(userId, &order.size);

    sqlite3_finalize(stmt);
    close_db(db);
    return order;
}

Order* get_all_orders_of_user(int userId, int *size){
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM Orders WHERE userId = ?;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        *size = 0;
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, userId);

    int rows = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        rows++;
    }

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    sqlite3_bind_int(stmt, 1, userId);

    Order *orders = malloc(rows * sizeof(Order));
    if (!orders) {
        fprintf(stderr, "Memory allocation failed for orders.\n");
        sqlite3_finalize(stmt);
        close_db(db);
        *size = 0;
        return NULL;
    }

    int index = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        char *values[3];
        for (int i = 0; i < 3; i++) {
            values[i] = (char *)sqlite3_column_text(stmt, i);
        }

        cast_row_to_order_struct(&orders[index], values);

        orders[index].items = get_order_items(values[0], &orders[index].size);
        index++;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    *size = rows;
    return orders;
}

Order* get_all_completed_orders(int *size){
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM Orders WHERE delivered = 1;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        *size = 0;
        return NULL;
    }

    int rows = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        rows++;
    }

    Order *orders = malloc(rows * sizeof(Order));
    if (!orders) {
        fprintf(stderr, "Memory allocation failed for orders.\n");
        sqlite3_finalize(stmt);
        close_db(db);
        *size = 0;
        return NULL;
    }

    int index = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        char *values[3];
        for (int i = 0; i < 3; i++) {
            values[i] = (char *)sqlite3_column_text(stmt, i);
        }

        cast_row_to_order_struct(&orders[index], values);

        orders[index].items = get_order_items(values[0], &orders[index].size);
        index++;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    *size = rows;
    return orders;
}

Order* get_all_pending_orders(int *size){
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt;

    const char *sql = "SELECT * FROM Orders WHERE delivered = 0;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        *size = 0;
        return NULL;
    }

    int rows = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        rows++;
    }

    Order *orders = malloc(rows * sizeof(Order));
    if (!orders) {
        fprintf(stderr, "Memory allocation failed for orders.\n");
        sqlite3_finalize(stmt);
        close_db(db);
        *size = 0;
        return NULL;
    }

    int index = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        char *values[3];
        for (int i = 0; i < 3; i++) {
            values[i] = (char *)sqlite3_column_text(stmt, i);
        }

        cast_row_to_order_struct(&orders[index], values);

        orders[index].items = get_order_items(values[0], &orders[index].size);
        index++;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    *size = rows;
    return orders;
}