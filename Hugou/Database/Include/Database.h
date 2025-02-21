#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include "Assistance_PreferenceHelper.h"

class Database :
    public QObject
{
    Q_OBJECT

public:
    Database();
    bool open();
    static bool exec(QSqlQuery query);

private:
    QSqlDatabase m_database;
    static void dealError(QString errorText);
};

