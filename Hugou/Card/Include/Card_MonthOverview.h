#pragma once
#include "Card.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QDate>

class MonthOverviewCard :
    public Card
{
public:
    MonthOverviewCard(QWidget* parent);
    void loadMonthView(QDate date, QFont monthContentFont);

private:
    QVBoxLayout* m_layout;
    QWidget* m_titleWidget;
    QHBoxLayout* m_titleWidgetLayout;
    QLabel* m_title;
    QWidget* m_actionWidget;
    QHBoxLayout* m_actionWidgetLayout;
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
    void setupUi();
};

