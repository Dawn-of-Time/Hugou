#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include "Database.h"
#include "Struct_Memo.h"
#include "Controller_MemoSetting.h"

class ScheduleController;

class ScheduleModel :
    public QObject
{
public:
    ScheduleModel();
    ~ScheduleModel();
    void addMemo(Memo& memo);   // 添加后，更新结构体中的ID
    void addMemoAndAwardRelation(int memoID, int awardID);
    void addMemoAndReferenceRelation(int memoID, int referenceID);
    void addMemoAndSubMemoRelation(int memoID, int subMemoID);
    void readMemoDatabase();
    void deleteMemoRequest(int ID);
    void deleteMemo(int ID);
    void updateMemo(int ID, QString propertyName, QString value);

private:
    friend class ScheduleController;
    MemoSettingModel* m_memoSettingModel;
    QList<Memo> m_memoList = {};
};

