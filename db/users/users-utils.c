#include "../../headers.h"

void cast_row_to_user_struct(User *userObject, char **values){
    userObject->id = atoi(values[0]);

    if (values[1]) {
        strncpy(userObject->name, values[1], sizeof(userObject->name) - 1);
        userObject->name[sizeof(userObject->name) - 1] = '\0';
    }

    if (values[2]) {
        strncpy(userObject->email, values[2], sizeof(userObject->email) - 1);
        userObject->email[sizeof(userObject->email) - 1] = '\0';
    }

    if (values[3]) {
        strncpy(userObject->role, values[3], sizeof(userObject->role) - 1);
        userObject->role[sizeof(userObject->role) - 1] = '\0';
    }

    if (values[4]) {
        strncpy(userObject->password, values[4], sizeof(userObject->password) - 1);
        userObject->password[sizeof(userObject->password) - 1] = '\0';
    }

    if (values[5]) {
        strncpy(userObject->phoneNumber, values[5], sizeof(userObject->phoneNumber) - 1);
        userObject->phoneNumber[sizeof(userObject->phoneNumber) - 1] = '\0';
    }

    if (values[6]) {
        strncpy(userObject->address, values[6], sizeof(userObject->address) - 1);
        userObject->address[sizeof(userObject->address) - 1] = '\0';
    }

    userObject->pincode = atoi(values[7]);

    if (values[8]) {
        strncpy(userObject->state, values[8], sizeof(userObject->state) - 1);
        userObject->state[sizeof(userObject->state) - 1] = '\0';
    }

    userObject->money = atoi(values[9]);
    userObject->createdAt = atoi(values[10]);
}

int is_email_taken(char *email){
    sqlite3* db = open_db();
    sqlite3_stmt *stmt;

    char *sql = "SELECT COUNT(*) FROM Users WHERE email = ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);

    int email_count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW){
        email_count = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    close_db(db);
    return email_count > 0 ? 1 : 0;
}

int count_all_users(){
    sqlite3 *db = open_db();

    char *sql = "SELECT COUNT(*) FROM Users;";
    int count = 0;
    char *errMsg = 0;

    if (sqlite3_exec(db, sql, countCallback, &count, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to count users: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    return count;
}