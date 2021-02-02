//
// Created by mason on 2021/1/18.
//

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>

bool createTable(QSqlQuery query, std::string tableName);
bool insertData(QSqlQuery query, std::string data);
int selectAllDate(QSqlQuery query);
void deleteFromData(QSqlQuery query);

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
    return EXIT_FAILURE;
  }

  selectAllDate(query);
  deleteFromData(query);

  database.close();
  return EXIT_SUCCESS;
}

bool createTable(QSqlQuery query, std::string tableName) {
  //  建表语句
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
  for (int i = 0; i < 10; ++i) {
    query.prepare(insertData);
    query.addBindValue("qwertyui");
    query.addBindValue("测试");
    query.addBindValue("localhost");
    query.addBindValue(QString::fromStdString("10.0.0." + std::to_string(i)));
    query.addBindValue(false);

    bool insertResult = query.exec();
    if (!insertResult) {
      qDebug() << query.lastError();
      continue;
    }
  }

  return true;
}

int selectAllDate(QSqlQuery query) {
  QString selectSql = "select * from hosts";
  if (!query.exec(selectSql)) {
    qDebug() << query.lastError();
  } else {
    while (query.next()) {
      int id = query.value(0).toInt();
      QString name = query.value(1).toString();
      QString domain = query.value(3).toString();
      QString ip = query.value(4).toString();
      qDebug() << QString("id:%1, name:%2, domain:%3, ip:%4")
                      .arg(id)
                      .arg(name)
                      .arg(domain)
                      .arg(ip);
    }
  }

  return 0;
}

void deleteFromData(QSqlQuery query) {
  QString deleteSql = "delete from hosts where id=?";
  query.prepare(deleteSql);
  query.addBindValue(22);
  if (!query.exec()) {
    qDebug() << query.lastError();
  } else {
    qDebug() << "deleted!";
  }
}
