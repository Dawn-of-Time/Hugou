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
#include "Include/Struct_Memo.h"
#include "View/Widgets/Include/MemoSettingItem.h"

class MemoSettingController;

class MemoSettingView :
    public QWidget
{

    Q_OBJECT

public:
    MemoSettingView(QWidget* parent, Memo* memo);
    void applyGeneralStyle(const MemoTemplate& memoTemplate);
    int getSuitableHeight() { return m_pageSuitableHeight + 30; }; // 25(m_templateWidget) + 5(spacing)
    void addMemoSettingItemToLayout(QWidget* widget);
    QParallelAnimationGroup* fadeIn();
    QParallelAnimationGroup* fadeOut();
    void enableGraphicEffect();
    void disableGraphicEffect();

signals:
    void memoInformationPrepared(const Memo& memo);

private:
    friend class MemoSettingController;
    int m_pageNum = 0;
    int m_occupiedHeight = 20;
    int m_maxPageHeight = 480;
    int m_maxPageNum = 3;
	int m_pageSuitableHeight = 20;
    QParallelAnimationGroup* m_fadeAnimationGroup;
    Memo* m_memo;
    QVBoxLayout* m_layout;
    QWidget* m_baseWidget;
    QVBoxLayout* m_baselayout;
    QWidget* m_templateWidget;
    QGraphicsOpacityEffect* m_templateWidgetEffect;
    QHBoxLayout* m_templateWidgetLayout;
    QLabel* m_templateTitle;
    QPushButton* m_templateButton;
    QPushButton* m_saveButton;
    QWidget* m_contentWidget;
    QGraphicsOpacityEffect* m_contentWidgetEffect;
    QHBoxLayout* m_contentWidgetLayout;
    QMap<MemoSettingItemType, QWidget*> m_memoContentMap = {};
    QList<QWidget*> m_pageList;

    void setupUi();
    void generateNewPage();
    void paintEvent(QPaintEvent* event) override;
    void check();
};

