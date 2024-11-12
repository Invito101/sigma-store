#include <sqlite3.h>

#ifndef HEADERS_H   // Prevents multiple inclusion
#define HEADERS_H

void clrscr(void);

sqlite3* open_db(void);
int create_tables(void);

#endif
