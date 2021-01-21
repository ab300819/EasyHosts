//
// Created by mason on 2021/1/18.
//

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <iostream>

int main(int argc, char* argv[]) {
  QString connectName = "hosts_sqlite";

  QSqlDatabase database;

  if (QSqlDatabase::contains(connectName)) {
    database = QSqlDatabase::database(connectName);
  } else {
    database = QSqlDatabase::addDatabase("QSQLITE", connectName);
    database.setDatabaseName("hosts.db");
  }

  qDebug() << "warn";

  auto createTableSql = R"~(create table hosts
(
    id       INTEGER not null primary key autoincrement,
    group_id INTEGER not null default 0,
    name     text    not null default '',
    domain   text    not null default '',
    ip       text    not null default '',
    flag     integer not null default 0,
    prop     INTEGER not null default 0
);)~";

  std::cout << createTableSql << std::endl;
  return EXIT_SUCCESS;
}