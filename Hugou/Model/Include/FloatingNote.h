#pragma once

#include <map>
#include <QObject>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QElapsedTimer>
#include <QTimer>
#include <QPainter>
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

    const std::map<Type, QString> typeText =
    {
        {Success, "Success"},
        {Information, "Information"},
        {Dialog, "Dialog"},
        {Warning, "Warning"},
        {Error, "Error"}
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
    inline void setType(Type type) { this->type = type; };
    inline void setContent(QString content) { this->content = content; };
    inline void setSubcontent(QString subcontent) { this->subcontent = subcontent; };
    inline void setHiddenPos(QPoint hiddenPos) { floatingNoteHiddenPos = hiddenPos; }
    inline void setShownPos(QPoint shownPos) { floatingNoteShownPos = shownPos; }
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
    QString subcontent = "";
    QTimer* updateTimer;
    QElapsedTimer* timer;

    const std::map<Type, QPixmap> typeIcon =
    {
        {Success, QPixmap("res/ico/success.png")},
        {Information, QPixmap("res/ico/information.png")},
        {Dialog, QPixmap("res/ico/dialog.png")},
        {Warning, QPixmap("res/ico/warning.png")},
        {Error, QPixmap("res/ico/error.png")}
    };
};

QT_END_NAMESPACE