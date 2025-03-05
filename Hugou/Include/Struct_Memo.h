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

struct MemoTypeLabel
{
    int ID = -1;
    QString name = "";

    bool operator!=(const MemoTypeLabel& other) const {
        return ID != other.ID || name != other.name;
    }
};

struct MemoType
{
    int ID = -1;
    QString name = "";
    QColor color = QColor();
    MemoTypeLabel label;
    int priority = 0;

    bool operator<(const MemoType& other) const {
        return ID < other.ID;
    }
    bool operator!=(const MemoType& other) const {
        return ID != other.ID || name != other.name || color != other.color || label != other.label || priority != other.priority;
    }
};

struct Memo
{
    int ID = -1;
    QString sketch = "";
    int memoType = 0;
    MemoTemplate memoTemplate = MemoTemplate
    {
        "Default",
        QColor("#377FED"),
        { Type, Time, ImportanceAndUrgency, Detail, SubMemo, Award, Reference }
    };
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
};