#pragma once

#include <map>
#include <QObject>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QElapsedTimer>
#include <QTimer>
#include "ui_FloatingNote.h"

QT_BEGIN_NAMESPACE

class Hugou;

class FloatingNote :
    public QWidget
{
    Q_OBJECT

public:
    enum Type
    {
        Success,
        Information,
        Dialog,
        Warning,
        Error
    };

    enum Feedback
    {
        Yes,
        No,
        DealLater
    };

    QPoint floatingNoteHiddenPos;
    QPoint floatingNoteShownPos;
    Type type = Success;

    FloatingNote(QWidget* HugouClass);
    ~FloatingNote();

    void updateUI();
    void setType(Type type);
    void setContent(QString content);
    inline void setHiddenPos(QPoint hiddenPos) { floatingNoteHiddenPos = hiddenPos; }
    inline void setShownPos(QPoint shownPos) { floatingNoteShownPos = shownPos; }
    QPropertyAnimation* moveNote(QPoint startValue, QPoint endValue);
    QPropertyAnimation* raiseNote();
    QPropertyAnimation* dropNote();

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
        {Success, QIcon("res/ico/success.png")},
        {Information, QIcon("res/ico/information.png")},
        {Dialog, QIcon("res/ico/dialog.png")},
        {Warning, QIcon("res/ico/warning.png")},
        {Error, QIcon("res/ico/error.png")}
    };

    const std::map<Type, QString> typeText =
    {
        {Success, "SUCCESS"},
        {Information, "INFORMATION"},
        {Dialog, "DIALOG"},
        {Warning, "WARNING"},
        {Error, "ERROR"}
    };
};

QT_END_NAMESPACE