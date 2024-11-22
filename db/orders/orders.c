#include "../../headers.h"

int place_order(int userId){
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO Orders(createdAt, userId) VALUES(?,?);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, getISTTime());
    sqlite3_bind_int(stmt, 2, userId);

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int orderId = (int)sqlite3_last_insert_rowid(db);

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    mark_cart_as_ordered(userId, orderId);
    return 0;
}