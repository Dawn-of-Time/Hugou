#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include "Const_Geometry.h"
#include "FloatingNote.h"
#include "ButtonHoverWatcher.h"
#include "Assistance_FloatingNoteManager.h"


QT_BEGIN_NAMESPACE

class HugouView;

class TitleBarView : public QWidget
{
    Q_OBJECT

public:
    TitleBarView(QWidget* parent);
    bool isOnMaxButton(QPoint windowPos);
    bool isOnDragZone(QPoint windowPos);

signals:
    void SignalMinimizeButtonClicked();
    void SignalScaleButtonClicked();
    void SignalCloseButtonClicked();
    void SignalFloatingNotePanelButtonClicked();
private:
    friend class HugouView;
    QHBoxLayout* m_titleLayout;
    QLabel* m_dragZone;
    QLabel* m_floatingNotePanelLabel;
    QVBoxLayout* m_floatingNotePanelLabelLayout;
    QLabel* m_floatingNotePanelButtonBackground;
    QVBoxLayout* m_floatingNotePanelButtonBackgroundLayout;
    QPushButton* m_floatingNotePanelButton;
    QPushButton* m_floatingNotePanelIcon;
    QHBoxLayout* m_queueLayout;
    QLabel* m_floatingNoteQueue;
    QLabel* m_firstNotePoint;
    QLabel* m_secondNotePoint;
    QLabel* m_thirdNotePoint;
    QLabel* m_forthNotePoint;
    QLabel* m_fifthNotePoint;
    QPixmap m_float_r = QPixmap(":/icon/float_r.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap m_float_b = QPixmap(":/icon/float_b.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap m_float_p = QPixmap(":/icon/float_p.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap m_float_o = QPixmap(":/icon/float_o.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap m_float_g = QPixmap(":/icon/float_g.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap m_float_w = QPixmap(":/icon/float_w.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    std::map<FloatingNote::Type, QPixmap> m_typePixmap =
    {
        {FloatingNote::Type::Success, m_float_g},
        {FloatingNote::Type::Dialog, m_float_p},
        {FloatingNote::Type::Information, m_float_b},
        {FloatingNote::Type::Warning, m_float_o},
        {FloatingNote::Type::Error, m_float_r}
    };
    std::vector<QLabel*> m_notePointQueue;
    QPushButton* m_helpButton;
    QPushButton* m_minimizeButton;
    QPushButton* m_scaleButton;
    QPushButton* m_closeButton;
    ButtonHoverWatcher* m_floatingNotePanelButtonHoverWatcher;
    //ButtonHoverWatcher* closeButtonHoverWatcher;
    //ButtonHoverWatcher* scaledButtonHoverWatcher;

    void setupUi();
    void slideFloatingNotePoint();
    void floatFloatingNotePoint();
    void allocateFloatingNotePoint();

    //void paintEvent(QPaintEvent* event) override;
};

QT_END_NAMESPACE