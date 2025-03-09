#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include "Utils/Include/Utils_MessegeHelper.h"

class Database :
    public QObject
{
    Q_OBJECT

public:
    Database();
    bool open();
    static bool exec(QSqlQuery& query);

private:
    QSqlDatabase m_database;
    static void raiseError(const QString& errorText);
    void createMemoDatabase();
    void createMemoTypeLabelDatabase();
    void createMemoTypeDatabase();
    void createAwardDatabase();
    void createReferenceDatabase();
    void createMemoAndAwardDatabase();
    void createMemoAndReferenceDatabase();
    void createMemoAndSubMemoDatabase();
};

