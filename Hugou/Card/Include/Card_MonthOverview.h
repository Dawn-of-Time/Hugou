#pragma once
#include "Card.h"
#include "CloseWhenLeaveWidget.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QGraphicsDropShadowEffect>
#include <QLineEdit>
#include <QIntValidator>


class MonthOverviewCard :
    public Card
{
public:
    MonthOverviewCard(QWidget* parent);
    

private:
    QDate m_currentDate = QDate();
    QPushButton* m_todayButton;
    QVBoxLayout* m_layout;
    QWidget* m_titleWidget;
    QHBoxLayout* m_titleWidgetLayout;
    QPushButton* m_title;
    QWidget* m_actionWidget;
    QHBoxLayout* m_actionWidgetLayout;
    QPushButton* m_backToTodayButton;
    QPushButton* m_backButton;
    QPushButton* m_forwardButton;
    QWidget* m_monthWidget;
    QVBoxLayout* m_monthWidgetLayout;
    QWidget* m_weekdaysBar;
    QHBoxLayout* m_weekdaysBarLayout;
    QList<QPushButton*> m_weekIndexButtonListForAMonth = {};
    QList<QPushButton*> m_dayListForAMonth = {};
    QList<QWidget*> m_weekListForAMonth = {};
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    QMap<QString, int> m_monthMap =
    {
        { "Jan", 1},
        { "Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec",  12}
    };
    void setupUi();
    void loadMonthView(QDate date);
    void goBackAMonth();
    void goForwardAMonth();
    void goBackToToday();
    void setYearAndMonth();
};

