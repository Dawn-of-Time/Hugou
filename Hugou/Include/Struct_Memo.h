#pragma once
#include <QString>
#include <QMap>
#include <QDateTime>
#include <QColor>

enum MemoImportanceAndUrgency
{
    UrgentAndImportant,
    NotUrgentButImportant,
    UrgentButNotImportant,
    NotUrgentAndNotImportant
};

enum MemoSettingItemType {
    Type, Time, ImportanceAndUrgency, Detail, SubMemo, Award, Reference
};

struct MemoTemplate
{
    QString name;
    QColor color;
    QList<MemoSettingItemType> templateContent;
};

const MemoTemplate defaultTemplate = MemoTemplate
{
    "Default",
    QColor("#377FED"),
    { Type, Time, ImportanceAndUrgency, Detail, SubMemo, Award, Reference }
};

struct MemoType
{
    QString name;
    QColor color;
};

struct Memo
{
    QString sketch = "";
    int memoType = 0;
    MemoTemplate memoTemplate = defaultTemplate;
    bool status = false;
    bool postponeFlag = false;
    QDateTime timePeriod_f = QDateTime();
    QDateTime timePeriod_l = QDateTime();
    QDateTime timePoint = QDateTime();
    MemoImportanceAndUrgency importanceAndUrgency = UrgentAndImportant;
    QString detail = "NULL";
    int retentionPeriod = -1;
    bool hasSubMemo = false;
    bool hasAward = false;
    bool hasReference = false;
    QList<int> subMemo = {};
    QList<int> award = {};
    QList<int> reference = {};
    int ID = -1;
};