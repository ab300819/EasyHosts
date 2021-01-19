//
// Created by mason on 2021/1/18.
//

#include <sqlite3.h>

#include <iostream>

int main(int argc, char* argv[]) {
  sqlite3* db;
  int rc;

  rc = sqlite3_open("hosts.db", &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
  } else {
    fprintf(stderr, "Opened database successfully\n");
  }
  sqlite3_close(db);
  return EXIT_SUCCESS;
}