#pragma once
#include <QObject>
#include "Include/Struct_Memo.h"
#include "Database/Include/Database.h"

class MemoSettingModel :
    public QObject
{
public:
    MemoSettingModel(QObject* parent);
    ~MemoSettingModel();

private:
    friend class MemoSettingController;
    QList<MemoTemplate*> m_templateList = {};
    QMap<int, MemoTypeLabel*> m_labelMap = {};
    QMap<int, QList<MemoType*>> m_typeLabelMap = {};
    QList<MemoTypeLabel*> m_typeLabelList = {};
    QList<MemoType*> m_typeList = {};
    void readMemoTypeData();
    void readMemoTypeLabelData();
};

