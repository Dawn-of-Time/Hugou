#pragma once

#include <map>
#include <QObject>
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QElapsedTimer>
#include <QTimer>
#include "ui_FloatingNote.h"

QT_BEGIN_NAMESPACE

class FloatingNote :
    public QWidget
{
    Q_OBJECT

public:
    enum class Type
    {
        Success,
        Information,
        Dialog,
        Warning,
        Error
    };

    enum class Feedback
    {
        Yes,
        No,
        DealLater
    };

    bool isShown = true;
    Type type = Type::Success;

    FloatingNote(QWidget* HugouClass);
    ~FloatingNote();

    void updateUI();
    void setType(Type type);
    void setContent(QString content);
    QPropertyAnimation* raiseNote();
    QPropertyAnimation* dropNote(QPoint startValue, QPoint endValue); // 因移出动画并不总是唯一的，所以要设置初始值和结束值

signals:
    void SignalButtonClicked(Feedback feedback);
    void SignalDealNow(FloatingNote* floatingNote);
    void SignalDealLater(FloatingNote* floatingNote);

protected slots:
    void SlotButtonClicked(Feedback feedback);
    void SlotTimekeeping();

private:
    Ui_FloatingNote ui;
    QString content = "";
    QTimer* updateTimer;
    QElapsedTimer* timer;

    const std::map<Type, QIcon> typeIcon =
    {
        {Type::Success, QIcon("res/ico/success.png")},
        {Type::Information, QIcon("res/ico/information.png")},
        {Type::Dialog, QIcon("res/ico/dialog.png")},
        {Type::Warning, QIcon("res/ico/warning.png")},
        {Type::Error, QIcon("res/ico/error.png")}
    };

    const std::map<Type, QString> typeText =
    {
        {Type::Success, "SUCCESS"},
        {Type::Information, "INFORMATION"},
        {Type::Dialog, "DIALOG"},
        {Type::Warning, "WARNING"},
        {Type::Error, "ERROR"}
    };
};

QT_END_NAMESPACE