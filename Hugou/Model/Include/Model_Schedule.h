#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include "Database.h"
#include "Struct_Task.h"


class ScheduleModel :
    public QObject
{
public:
    ScheduleModel();
    ~ScheduleModel();
    void addTask(Task& task);   // ��Ӻ󣬸��½ṹ���е�ID
    void deleteTaskRequest(int ID);
    void deleteTask(int ID);
    void updateTask(int ID, QString propertyName, QString value);

private:
    Database* m_database;
};

