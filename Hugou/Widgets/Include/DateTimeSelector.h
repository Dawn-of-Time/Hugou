#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QLineEdit>
#include "Widgets/Include/FadeEffectButton.h"

class DateTimeSelector :
    public QWidget
{
public:
    DateTimeSelector(QWidget* parent);
    void setDate(const QDate& date);
    void setTime(const QTime& time);
    void setDateTime(const QDateTime& dateTime);

private:
    QDateTime m_selectedDateTime;
    QIntValidator* m_yearValidator;
    QIntValidator* m_monthValidator;
    QIntValidator* m_dayValidator;
    QIntValidator* m_hourValidator;
    QIntValidator* m_minuteValidator;
    QVBoxLayout* m_layout;
    QLineEdit* m_lineEdit;
    QWidget* m_YYYYMMDDWidget;
    QHBoxLayout* m_YYYYMMDDWidgetLayout;
    FadeEffectButton* m_yearButton;
    FadeEffectButton* m_monthButton;
    FadeEffectButton* m_dayButton;
    QWidget* m_HHMMWidget;
    QHBoxLayout* m_HHMMWidgetLayout;
    FadeEffectButton* m_hourButton;
    FadeEffectButton* m_minuteButton;

    void setupUi();
    void edit(FadeEffectButton* button, const QValidator* validator);
};

