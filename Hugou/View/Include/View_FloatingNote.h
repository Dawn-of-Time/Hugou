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
#include "Const_Geometry.h"

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
    inline void setType(NoteType type) { this->m_type = type; };
    inline void setContent(QString content) { this->m_content = content; };
    inline void setSubcontent(QString subcontent) { this->m_subcontent = subcontent; };
    inline void setHiddenPos(QPoint hiddenPos) { m_floatingNoteHiddenPos = hiddenPos; }
    inline void setShownPos(QPoint shownPos) { m_floatingNoteShownPos = shownPos; }
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
    QFrame* m_floatingNoteFrame;
    QWidget* m_signZone;
    QLabel* m_contentZone;
    QLabel* m_subcontentZone;
    QWidget* m_buttonZone;
    QVBoxLayout* m_floatingNoteLayout;
    QVBoxLayout* m_floatingNoteFrameLayout;
    QHBoxLayout* m_signLayout;
    QLabel* m_signIcon;
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

    const std::map<NoteType, QPixmap> m_typeIcon =
    {
        {Success, QPixmap(":/icon/success.ico")},
        {Information, QPixmap(":/icon/information.ico")},
        {Dialog, QPixmap(":/icon/dialog.ico")},
        {Warning, QPixmap(":/icon/warning.ico")},
        {Error, QPixmap(":/icon/error.ico")}
    };

    void setupUi();
};

QT_END_NAMESPACE