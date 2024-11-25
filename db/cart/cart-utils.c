#include "../../headers.h"

int count_cart_items_of_user(int userId){
    sqlite3 *db = open_db();

    int count = 0;
    sqlite3_stmt *stmt;

    char *sql = "SELECT COUNT(*) FROM Cart WHERE userId = ? AND orderId IS NULL;";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, userId);

    if (sqlite3_step(stmt) == SQLITE_ROW){
        count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return count;
}

void cast_row_to_cart_struct(Cart *cartObject, char **values){
    cartObject->id = atoi(values[0]);
    cartObject->quantity = atoi(values[1]);
    cartObject->userId = atoi(values[2]);
    cartObject->productId = atoi(values[3]);
    cartObject->orderId = atoi(values[4]);
}