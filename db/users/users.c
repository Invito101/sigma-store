#include "../../headers.h"

int create_user(char *role, char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    sqlite3 *db = open_db();
    if(db == NULL) return 1;
    char *errMsg = 0;

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO USERS(name, email, role, password, phoneNumber, address, pincode, state, money) VALUES(?,?,?,?,?,?,?,?,?);";

    int rc = rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    if(rc != SQLITE_OK){
        fprintf(stderr, "%s: Preparation of Statement : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    char *encryptedPassword = encrypt(password);

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, role, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, encryptedPassword, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, phoneNumber, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, address, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 7, pincode);
    sqlite3_bind_text(stmt, 8, state, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, 0);

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

int create_customer(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Customer", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int create_seller(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Seller", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int create_admin(char *name, char *email, char *password, char *phoneNumber, char *address, int pincode, char *state){
    create_user("Admin", name, email, password, phoneNumber, address, pincode, state);

    return 0;
}

int countCallback(void *count, int argc, char **argv, char **azColName){
    *(int *)count = atoi(argv[0]);
    return 0;
}

int count_all_users(){
    sqlite3 *db = open_db();

    char *sql = "SELECT COUNT(*) FROM Users;";
    int count = 0;
    char *errMsg = 0;

    if (sqlite3_exec(db, sql, countCallback, &count, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "%s : Failed to count users: %s\n", __func__, sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    return count;
}

typedef struct {
    User *users;
    int currentIndex;
} UserArrayWrapper;

int dataCallback(void *userWrapper, int argc, char **argv, char **azColName) {
    UserArrayWrapper *wrapper = (UserArrayWrapper *)userWrapper;
    User *userObject = &wrapper->users[wrapper->currentIndex];

    userObject->id = atoi(argv[0]);

    if (argv[1]) {
        strncpy(userObject->name, argv[1], sizeof(userObject->name) - 1);
        userObject->name[sizeof(userObject->name) - 1] = '\0';
    }

    if (argv[2]) {
        strncpy(userObject->email, argv[2], sizeof(userObject->email) - 1);
        userObject->email[sizeof(userObject->email) - 1] = '\0';
    }

    if (argv[3]) {
        strncpy(userObject->role, argv[3], sizeof(userObject->role) - 1);
        userObject->role[sizeof(userObject->role) - 1] = '\0';
    }

    if (argv[4]) {
        strncpy(userObject->password, argv[4], sizeof(userObject->password) - 1);
        userObject->password[sizeof(userObject->password) - 1] = '\0';
    }

    if (argv[5]) {
        strncpy(userObject->phoneNumber, argv[5], sizeof(userObject->phoneNumber) - 1);
        userObject->phoneNumber[sizeof(userObject->phoneNumber) - 1] = '\0';
    }

    if (argv[6]) {
        strncpy(userObject->address, argv[6], sizeof(userObject->address) - 1);
        userObject->address[sizeof(userObject->address) - 1] = '\0';
    }

    userObject->pincode = atoi(argv[7]);

    if (argv[8]) {
        strncpy(userObject->state, argv[8], sizeof(userObject->state) - 1);
        userObject->state[sizeof(userObject->state) - 1] = '\0';
    }

    userObject->money = atoi(argv[9]);
    userObject->createdAt = parseDateToTimeT(argv[10]);

    wrapper->currentIndex++;
    return 0;
}

User* get_all_users(int *size) {
    sqlite3 *db = open_db();

    char *errMsg = 0;
    int count = count_all_users();
    if (count <= 0) {
        *size = 0;
        sqlite3_close(db);
        return NULL;
    }

    User *users = malloc(count * sizeof(User));
    if (!users) {
        fprintf(stderr, "Memory allocation failed\n");
        sqlite3_close(db);
        return NULL;
    }

    UserArrayWrapper wrapper = { .users = users, .currentIndex = 0 };

    char *sql = "SELECT * FROM Users";
    int rc = sqlite3_exec(db, sql, dataCallback, &wrapper, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "%s: Execution of Query : %s\n", __func__, errMsg ? errMsg : sqlite3_errmsg(db));
        sqlite3_free(errMsg);
        sqlite3_close(db);
        free(users);
        return NULL;
    }

    sqlite3_close(db);
    *size = count;
    return users;
}