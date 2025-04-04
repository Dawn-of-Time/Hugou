#pragma once
#include "CloseWhenLeaveWidget.h"
#include "FadeEffectButton.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>

class YearAndMonthSelector :
    public CloseWhenLeaveWidget
{
    Q_OBJECT

public:
    YearAndMonthSelector(int selectedYear, int selectedMonth, QWidget* parent);

signals:
    void SignalSelected(int year, int month);

private:
    int m_selectedYear;
    QList<QString> m_monthNameList = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    QMap<QString, int> m_monthMap =
    {
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec", 12}
    };
	QVBoxLayout* m_layout;
	QWidget* m_titleWidget;
	QHBoxLayout* m_titleWidgetLayout;
	QPushButton* m_backButton;
	QLineEdit* m_yearLineEdit;
	QPushButton* m_forwardButton;
	QWidget* m_monthWidget;
	QGridLayout* m_monthWidgetLayout;
	FadeEffectButton* m_currentMonthbutton;
	
    void setupUi();
    void changeYear(int year);
};
