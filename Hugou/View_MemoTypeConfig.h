#pragma once
#include "PopupWidget.h"

class MemoTypeConfigView :
    public PopupWidget
{
    Q_OBJECT

public:
    MemoTypeConfigView(QWidget* parent = nullptr);

private:
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
};

