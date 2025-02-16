#pragma once
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QPropertyAnimation>
#include "FadeEffectButton.h"
#include "Struct_Task.h"

class TaskSettingController;

class TaskSettingView :
    public QWidget
{
    Q_OBJECT

public:
    explicit TaskSettingView(QWidget* parent);
    void slideIn();
    void slideOut();
    void adjustView();

private:
    enum AnimationFlag
    {
        SlideIn,
        SlideOut
    };
    friend class TaskSettingController;
    QVBoxLayout* m_taskSettingLayout;
    QWidget* m_general;
    QVBoxLayout* m_generalLayout;
    QWidget* m_title;
    QHBoxLayout* m_titleLayout;
    QLabel* m_titleLabel;
    QPushButton* m_closeButton;
    QWidget* m_list;
    QVBoxLayout* m_listLayout;
    QWidget* m_sketchWidget;
    QVBoxLayout* m_sketchWidgetLayout;
    QLabel* m_sketchTitle;
    QLineEdit* m_sketch;
    QWidget* m_taskTypeWidget;
    QVBoxLayout* m_taskTypeWidgetLayout;
    QLabel* m_taskTypeTitle;
    QWidget* m_briefTaskTypeWidget;
    QHBoxLayout* m_briefTaskTypeWidgetLayout;
    QWidget* m_detailedTaskTypeWidget;
    QVBoxLayout* m_detailedTaskTypeWidgetLayout;
    FadeEffectButton* m_addTaskTypeButton;
    QWidget* m_timeWidget;
    QVBoxLayout* m_timeWidgetLayout;
    QLabel* m_timeTitle;
    QWidget* m_time;
    QPushButton* m_showOrHideButton;
    QWidget* m_postponeWidget;
    QVBoxLayout* m_postponeWidgetLayout;
    QLabel* m_postponeTitle;
    QWidget* m_importanceWidget;
    QVBoxLayout* m_importanceWidgetLayout;
    QLabel* m_importanceTitle;
    QWidget* m_detailWidget;
    QVBoxLayout* m_detailWidgetLayout;
    QLabel* m_detailTitle;
    QLineEdit* m_detail;
    QWidget* m_awardWidget;
    QVBoxLayout* m_awardWidgetLayout;
    QLabel* m_awardTitle;
    QLineEdit* m_award;
    QWidget* m_planPanel;
    QPushButton* m_commitButton;
    QPropertyAnimation* m_slideAnimation = nullptr;
    AnimationFlag m_animationFlag = AnimationFlag::SlideIn;
    bool m_isShown = false;
    void setupUi();
};