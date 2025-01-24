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
    void addTask(Task& task);   // 添加后，更新结构体中的ID
    void deleteTaskRequest(int ID);
    void deleteTask(int ID);
    void updateTask(int ID, QString propertyName, QString value);

private:
    Database* m_database;
};

