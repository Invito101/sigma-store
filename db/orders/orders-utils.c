#include "../../headers.h"

void cast_row_to_order_struct(Order *orderObject, char **values){
    orderObject->id = atoi(values[0]);
    orderObject->userId = atoi(values[1]);
    orderObject->createdAt = atoi(values[2]);
}

int count_all_orders_of_user(int userId){
    int count = 0;
    sqlite3 *db = open_db();

    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM Cart WHERE userId = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, userId);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        count = atoi((const char*)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return count;
}