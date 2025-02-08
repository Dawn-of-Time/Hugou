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
        MemoType{ "Work", Qt::red },
        MemoType{ "Learn", Qt::blue },
        MemoType{ "Recreation", Qt::green },
    };
};

