#pragma once
#include "Widgets/Include/MemoSettingItem/MemoSettingItem.h"
#include "Include/Struct_Memo.h"
#include "View/Include/View_MemoTypeConfig.h"
#include "View/Widgets/Include/MemoTypeWidget.h"

class MemoTypeItem :
    public MemoSettingItem
{
    Q_OBJECT
public:
    MemoTypeItem(const QList<MemoTypeLabel*>& typeLabelList, QMap<int, QList<MemoType*>>& typeLabelMap, QList<MemoType*>& typeList, QWidget* parent = nullptr);
    void addMemoType(MemoType& memoType);
    bool getResult(MemoType* memoType);

private:
    bool m_isSelected = false;
    MemoType* m_selectedMemoType;
    QMap<int, QList<MemoType*>>& m_typeLabelMap;
    const QList<MemoTypeLabel*>& m_typeLabelList;
    QList<MemoType*>& m_typeList;
    int m_count = 0;
    QMap<MemoType*, MemoTypeWidget*> m_memoTypeWidgetMap;
    QList<MemoType*> m_priorityTypeList;
    QMap<MemoType*, MemoType*> m_oldNewPriorityDisplayMemoTypeMap = {};
    QMap<MemoType*, MemoType*> m_oldNewMemoTypeMap = {};
    QHBoxLayout* m_contentLayout;
    QWidget* m_typeListWidget;
    QHBoxLayout* m_typeListWidgetLayout;
    QPushButton* m_addTypeButton;
    void setupUi();
    void showMemoTypeConfigView();
};

