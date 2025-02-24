#pragma once
#include <QObject>
#include "Struct_Memo.h"
#include "Database.h"

class MemoSettingModel :
    public QObject
{
public:
    MemoSettingModel();

private:
    friend class MemoSettingController;
    QList<MemoTemplate> m_templateList = { defaultTemplate };
    QMap<int, MemoTypeLabel> m_labelMap = {};
    QMap<int, QList<MemoType>> m_typeLabelMap = {};
    QList<MemoTypeLabel> m_typeLabelList = {};
    QList<MemoType> m_typeList = {};
    QList<MemoType> m_priorityTypeList = {};
    void readMemoTypeData();
    void readMemoTypeLabelData();
};

