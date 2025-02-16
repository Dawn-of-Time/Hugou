#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxlayout>
#include <QLabel>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QPropertyAnimation>
#include <QScrollArea>
#include "Struct_Memo.h"
#include "MemoSettingItem.h"

class MemoSettingController;

class MemoSettingView :
    public QWidget
{

    Q_OBJECT

public:
    MemoSettingView(QWidget* parent, Memo memo);
    void applyGeneralStyle(MemoTemplate memoTemplate);
    QWidget* addMemoSettingItem(MemoSettingItemType itemType);
    const int getSuitableHeight() { return m_pageSuitableHeight + 50; };
    void fadeIn();

private:
    friend class MemoSettingController;
    int m_pageNum = 0;
    int m_occupiedHeight = 10;
    int m_maxPageHeight = 480;
    int m_maxPageNum = 3;
	int m_pageSuitableHeight = 10;
    Memo m_memo;
    QScrollArea* m_area;
    QGraphicsOpacityEffect* m_effect;
    QVBoxLayout* m_layout;
    QWidget* m_baseWidget;
    QVBoxLayout* m_baselayout;
    QWidget* m_templateWidget;
    QHBoxLayout* m_templateWidgetLayout;
    QLabel* m_templateTitle;
    QPushButton* m_templateButton;
    QWidget* m_contentWidget;
    QHBoxLayout* m_contentWidgetLayout;
    QMap<MemoSettingItemType, QWidget*> m_memoContentMap = {};
    QList<QWidget*> m_pageList;

    void setupUi();
    void generateNewPage();
    void enableGraphicEffect();
	void disableGraphicEffect();
    void paintEvent(QPaintEvent* event) override;
};

