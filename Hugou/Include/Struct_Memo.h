#pragma once
#include <QString>
#include <QMap>
#include <QDateTime>
#include <QColor>

enum MemoImportance
{
    UrgentAndImportant,
    NotUrgentButImportant,
    UrgentButNotImportant,
    NotUrgentAndNotImportant
};

enum MemoSettingItemType {
    Type, Time, Importance, Detail, SubMemo, Award, Reference
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
    { Type, Time, Importance, Detail, SubMemo, Award, Reference }
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
    MemoImportance importance = UrgentAndImportant;
    int importanceDegree = -1;
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