#pragma once
#include <QString>

enum TaskStatus
{
    Unfinished,
    Finished
};
enum TaskImportance
{
    UrgentAndImportant,
    NotUrgentButImportant,
    UrgentButNotImportant,
    NotUrgentAndNotImportant
};
struct Task
{
    QString sketch = "";
    int taskType = 0;
    TaskStatus status = Unfinished;
    bool postponeFlag = false;
    QString timePeriod_f = "NULL";
    QString timePeriod_l = "NULL";
    QString timePoint = "NULL";
    TaskImportance importance = UrgentAndImportant;
    QString detail = "NULL";
    QString award = "NULL";
    int preTask = -1;
    int postTask = -1;
    int retentionPeriod = -1;
    int ID = -1;
};

const QMap<QString, QString> taskTypeMap = 
{ 
    {"Work", "red"},
    {"Learn", "blue"},
    {"Recreation", "green"},
};