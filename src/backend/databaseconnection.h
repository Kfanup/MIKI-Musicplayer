#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QStandardPaths>
#include <QDebug>

static bool createConnection()
{
    QDir dir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation).first());
    if (!dir.exists()) {
        dir.mkpath(QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).first());
        dir.setPath(
            QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).first());
    }
    QString cachePath = dir.absolutePath() + QString("/mikimusic.sqlite");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(cachePath);
    if (!db.open()) {
        qCritical() << db.lastError() << "please check " << cachePath;
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS mymusic (hash TEXT primary key, "
               "timestamp INTEGER, "
               "title VARCHAR(256), author VARCHAR(256), "
               "album VARCHAR(256), mediatype VARCHAR(256), "
               "offset INTEGER, length INTEGER, "
               "size INTEGER, search_id INTEGER(256), "
               "favourite INTEGER(32), ");
    query.exec("CREATE TABLE IF NOT EXISTS playlist (id TEXT primary key not null, "
               "displayname VARCHAR(4096), "
               "sort_type INTEGER(16), sort_id INTEGER(16), ");
    query.exec("CREATE TABLE IF NOT EXISTS artist (id int primary key not null, "
               "name VARCHAR(20))");
    return true;
}
