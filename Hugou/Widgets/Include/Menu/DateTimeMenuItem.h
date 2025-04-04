#pragma once
#include "MenuItem.h"
#include <QDateTime>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QLineEdit>
#include "Widgets/Include/FadeEffectButton.h"

class DateTimeMenuItem :
    public MenuItem
{
    Q_OBJECT
public:
    DateTimeMenuItem(const QString& title, QWidget* menu);
    void setDateTime(const QDateTime& dateTime);
    QString save() override;

private:
    QDateTime m_selectedDateTime;
    QIntValidator* m_yearValidator;
    QIntValidator* m_monthValidator;
    QIntValidator* m_dayValidator;
    QIntValidator* m_hourValidator;
    QIntValidator* m_minuteValidator;
    QWidget* m_centralWidget;
    QHBoxLayout* m_layout;
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

