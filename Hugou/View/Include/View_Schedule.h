#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QDate>
#include <cmath>
#include "Const_Font.h"

class ScheduleView : public QWidget
{
    Q_OBJECT
public:
    ScheduleView(QWidget* parent);

private:
    QVBoxLayout* m_scheduleLayout;
    QWidget* m_viewSwitchBar;
    QHBoxLayout* m_viewSwitchBarLayout;
    QPushButton* m_dayViewSwitchButton;
    QPushButton* m_weekViewSwitchButton;
    QPushButton* m_monthViewSwitchButton;
    QWidget* m_scheduleWidget;
    QWidget* m_weekdaysBar;
    QHBoxLayout* m_weekdaysBarLayout;
    QVBoxLayout* m_scheduleWidgetLayout;

    void setupUi();
};