#pragma once

#include <map>
#include <QWidget>
#include <QObject>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QElapsedTimer>
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include "Include/Const_Geometry.h"

QT_BEGIN_NAMESPACE

class FloatingNote :
    public QWidget
{
    Q_OBJECT

public:
    enum NoteType
    {
        Success,
        Information,
        Dialog,
        Warning,
        Error
    };

    const std::map<NoteType, QString> m_typeText =
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

    QPoint m_floatingNoteHiddenPos;
    QPoint m_floatingNoteShownPos;
    NoteType m_type = Success;

    FloatingNote(QWidget* HugouClass);
    ~FloatingNote();

    void updateUI();
    inline void setType(const NoteType& type) { this->m_type = type; };
    inline void setContent(const QString& content) { this->m_content = content; };
    inline void setSubcontent(const QString& subcontent) { this->m_subcontent = subcontent; };
    inline void setHiddenPos(const QPoint& hiddenPos) { m_floatingNoteHiddenPos = hiddenPos; }
    inline void setShownPos(const QPoint shownPos) { m_floatingNoteShownPos = shownPos; }
    QPropertyAnimation* raiseNote();
    QPropertyAnimation* dropNote();

signals:
    void SignalButtonClicked(const Feedback& feedback);
    void SignalDealNow(FloatingNote* floatingNote);
    void SignalDealLater(FloatingNote* floatingNote);

protected slots:
    void SlotButtonClicked(const Feedback& feedback);
    void SlotTimekeeping();

private:
    QFrame* m_floatingNoteFrame;
    QWidget* m_signZone;
    QLabel* m_contentZone;
    QLabel* m_subcontentZone;
    QWidget* m_buttonZone;
    QVBoxLayout* m_floatingNoteLayout;
    QVBoxLayout* m_floatingNoteFrameLayout;
    QHBoxLayout* m_signLayout;
    QPushButton* m_signIcon;
    QLabel* m_signTitle;
    QLabel* m_timekeepingLabel;
    QHBoxLayout* m_buttonLayout;
    QPushButton* m_yesButton;
    QPushButton* m_noButton;
    QPushButton* m_dealLaterButton;
    QPoint m_hiddenPos;
    QPoint m_shownPos;
    QString m_content = "";
    QString m_subcontent = "";
    QTimer* m_updateTimer;
    QElapsedTimer* m_timer;

    const std::map<NoteType, QIcon> m_typeIcon =
    {
        {Success, QIcon(":/icon/success.ico")},
        {Information, QIcon(":/icon/information.ico")},
        {Dialog, QIcon(":/icon/dialog.ico")},
        {Warning, QIcon(":/icon/warning.ico")},
        {Error, QIcon(":/icon/error.ico")}
    };

    void setupUi();
};

QT_END_NAMESPACE