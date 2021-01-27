//
// Created by mason on 2021/1/18.
//

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>

bool createTable(QSqlQuery database, std::string tableName);
bool insertData(QSqlQuery query, std::string data);

int main(int argc, char* argv[]) {
  QString connectName = "hosts_sqlite";

  QSqlDatabase database;

  qDebug() << QSqlDatabase::drivers();

  if (QSqlDatabase::contains(connectName)) {
    database = QSqlDatabase::database(connectName);
  } else {
    database = QSqlDatabase::addDatabase("QSQLITE", connectName);
    database.setDatabaseName("hosts.db");
  }

  if (!database.open()) {
    qDebug() << "Failed to connect database." << database.lastError();
    return EXIT_FAILURE;
  }

  auto tableList = database.tables();
  qDebug() << tableList;

  QSqlQuery query(database);

  bool containTargetTable = tableList.contains("hosts");
  if (!containTargetTable) {
    qDebug() << "contain table status: " << containTargetTable;
    bool createResult = createTable(query, "");
    if (!createResult) {
      return EXIT_FAILURE;
    }
  }

  bool insertResult = insertData(query, "1");
  if (!insertResult) {
    qDebug() << "insert occur error";
  }

  database.close();
  return EXIT_SUCCESS;
}

bool createTable(QSqlQuery query, std::string tableName) {
  //  �������
  auto createTableSql = R"~(create table hosts(
    id       INTEGER not null primary key autoincrement,
    group_id INTEGER not null default 0,
    name     text    not null default '',
    domain   text    not null default '',
    ip       text    not null default '',
    flag     integer not null default 0,
    prop     INTEGER not null default 0);)~";

  query.prepare(QString::fromStdString(createTableSql));
  if (!query.exec()) {
    qDebug() << "failed to create table." << query.lastError();
    return false;
  } else {
    qDebug() << "tabled created";
    return true;
  }
}
bool insertData(QSqlQuery query, std::string data) {
  QString insertData =
      "INSERT INTO hosts(group_id, name, domain, ip, flag) VALUES (?,?,?,?,?)";
  query.prepare(insertData);
  for (int i = 0; i < 10; ++i) {
    query.addBindValue("qwertyui");
    query.addBindValue("����");
    query.addBindValue("localhost");
    query.addBindValue(QString::fromStdString("10.0.0." + std::to_string(i)));
    query.addBindValue(false);

    bool insertResult = query.exec();
    if (insertResult) {
      return true;
    } else {
      qDebug() << query.lastError();
      return false;
    }
  }

  return false;
}