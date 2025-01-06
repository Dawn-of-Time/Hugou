#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTemporaryFile>
#include <QDir>
#include "Assistance_SettingsHelper.h"
#include "Windows.h"

class Database :
    public QObject
{
    Q_OBJECT

public:
    Database();
    bool open();
    bool exec(QSqlQuery query);

private:
    QSqlDatabase m_database;

    void dealError(QString errorText);
};

