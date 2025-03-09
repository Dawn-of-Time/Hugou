#pragma once
#include "Database/Include/Database.h"
#include "Include/Struct_Memo.h"
#include "Menu/Include/ColorPaletteMenuItem.h"
#include "Menu/Include/LineEditMenuItem.h"
#include "Menu/Include/Menu.h"
#include "View/Widgets/Include/MemoTypeWidget.h"
#include "Widgets/Include/PopupWidget.h"

class MemoTypeConfigView :
    public PopupWidget
{
    Q_OBJECT

public:
    MemoTypeConfigView(QMap<MemoType*, MemoType*>& oldNewPriorityDisplayMemoTypeMap);
    ~MemoTypeConfigView();
    void addPriorityType(MemoType& memoType);
    void addTypeLabelAndType(const QString& labelName, QList<MemoType*>& typeList);
    void close();

signals:
    void SignalClose();

private:
    QMap<MemoType*, MemoTypeWidget*> m_priorityDisplayMemoTypeWidgetMap = {};
    QMap<MemoType*, MemoTypeWidget*> m_memoTypeWidgetMap = {};
    QMap<MemoType*, MemoType*>& m_oldNewPriorityDisplayMemoTypeMap;
    QMap<MemoType*, MemoType*> m_oldNewMemoTypeMap = {};
    QWidget* m_centralWidget;
    QVBoxLayout* m_layout;
    QWidget* m_priorityDisplayWidget;
    QVBoxLayout* m_priorityDisplayWidgetLayout;
    QLabel* m_priorityDisplayTitle;
    QWidget* m_priorityDisplayContent;
    QHBoxLayout* m_priorityDisplayContentLayout;
    QWidget* m_typeRepoWidget;
    QVBoxLayout* m_typeRepoWidgetLayout;
    QLabel* m_typeRepoTitle;
    QWidget* m_typeRepoContent;
    QVBoxLayout* m_typeRepoContentLayout;
    void setupUi();
    void showMemoTypeMenu(MemoTypeWidget* memoTypeWidget, const QPoint& shownPos);
};

