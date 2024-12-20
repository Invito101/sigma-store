#include "../../headers.h"

int create_user(char *role, char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    sqlite3 *db = open_db();
    char *errMsg = 0;

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO users(name, email, role, password, phoneNumber, address, pincode, state, money, createdAt) VALUES(?,?,?,?,?,?,?,?,?,?);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        close_db(db);
        return 1;
    }

    char *encryptedPassword = encrypter(password);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, role, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, encryptedPassword, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, phoneNumber, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, address, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, pincode);
    sqlite3_bind_text(stmt, 8, state, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, 0);
    sqlite3_bind_int(stmt, 10, getISTTime());

    rc = sqlite3_step(stmt);

    if(rc != SQLITE_DONE){
        fprintf(stderr, "%s: Execution of Statement : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        close_db(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return 0;
}

int create_customer(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Customer", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int create_admin(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Admin", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int dataCallback(void *data, int argc, char **argv, char **azColName) {
    UserArrayWrapper *wrapper = (UserArrayWrapper *) data;
    User *userObject = &wrapper->users[wrapper->currentIndex];

    cast_row_to_user_struct(userObject, argv);

    wrapper->currentIndex++;
    return 0;
}

User* get_all_users(int *size) {
    sqlite3 *db = open_db();

    char *errMsg = 0;
    int count = count_all_users();
    if (count <= 0) {
        *size = 0;
        close_db(db);
        return NULL;
    }

    User *users = malloc(count * sizeof(User));
    if (!users) {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        close_db(db);
        return NULL;
    }

    UserArrayWrapper wrapper = { .users = users, .currentIndex = 0 };

    char *sql = "SELECT * FROM Users";
    int rc = sqlite3_exec(db, sql, dataCallback, &wrapper, &errMsg);

    if (rc != SQLITE_OK){
        fprintf(stderr, "%s: Execution of Query : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        close_db(db);
        free(users);
        return NULL;
    }

    close_db(db);
    *size = count;
    return users;
}

User* login(char *email, char *password){
    sqlite3 *db = open_db();

    char *encryptedPassword = encrypter(password);

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Users WHERE email = ? AND password = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, encryptedPassword, -1, SQLITE_STATIC);

    User *user = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW){
        user = malloc(sizeof(User));
        if (user) {
            char *values[11];
            for (int i = 0; i < 11; i++){
                values[i] = (char *)sqlite3_column_text(stmt, i);
            }

            cast_row_to_user_struct(user, values);
        }
    }
    
    sqlite3_finalize(stmt);
    close_db(db);
    return user;
}

int get_money_of_user(char *email){
    sqlite3* db = open_db();
    int money = 0;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT money FROM Users WHERE email = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        money = atoi((const char*)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    close_db(db);
    return money;
}

int get_id_of_user_by_email(char *email){
    sqlite3* db = open_db();
    int id;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT id FROM Users WHERE email = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW){
        id = atoi((const char*)sqlite3_column_text(stmt, 0));
    }

    sqlite3_finalize(stmt);
    close_db(db);
    return id;
}

int modify_money_of_user(char *email, int new_money){
    sqlite3* db = open_db();
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE Users SET money = ? WHERE email = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, new_money);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE){
        fprintf(stderr, "%s : Failed to update record: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        close_db(db);
        return -1;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return 0;
}

User* get_user_by_id(int userId){
    sqlite3 *db = open_db();

    User *user = malloc(sizeof(User));
    if (!user) {
        fprintf(stderr, "%s: Memory allocation failed\n", __func__);
        close_db(db);
        return NULL;
    }

    sqlite3_stmt *stmt;
    const char *sql = "SELECT * FROM Users WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
        fprintf(stderr, "%s : Failed to prepare statement: %s\n", __func__, sqlite3_errmsg(db));
        close_db(db);
        free(user);
        return NULL;
    }

    sqlite3_bind_int(stmt, 1, userId);

    if (sqlite3_step(stmt) != SQLITE_ROW){
        fprintf(stderr, "%s : Failed to get record: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        close_db(db);
        free(user);
        return NULL;
    }

    char *values[11];
    for (int i = 0; i < 11; i++){
        values[i] = (char *) sqlite3_column_text(stmt, i);
    }

    cast_row_to_user_struct(user, values);

    sqlite3_finalize(stmt);
    close_db(db);
    return user;
}