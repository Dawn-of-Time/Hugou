#pragma once
#include <QObject>
#include "Struct_Memo.h"

class MemoSettingModel :
    public QObject
{
public:
    MemoSettingModel();

private:
    friend class MemoSettingController;
    QList<MemoTemplate> m_templateList = { defaultTemplate };
    QList<MemoType> m_typeList = {
        MemoType{ "Work", QColor("#ff6666")},
        MemoType{ "Learn", QColor("#009999") },
        MemoType{ "Recreation", QColor("#33ccff") },
        MemoType{ "Travle", QColor("#FF8C69") },
        MemoType{ "Test", QColor("#cc66cc") }
    };
};

