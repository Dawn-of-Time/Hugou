#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include <QLineEdit>
#include "View_FloatingNote.h"
#include "Assistance/Include/Assistance_ButtonHoverWatcher.h"
#include "Assistance/Include/Assistance_PictureHelper.h"

QT_BEGIN_NAMESPACE

class HugouView;

class TitleBarView : public QWidget
{
    Q_OBJECT

public:
    TitleBarView(QWidget* parent);
    bool isOnMaxButton(const QPoint& windowPos);
    bool isOnDragZone(const QPoint& windowPos);

signals:
    void SignalMinimizeButtonClicked();
    void SignalScaleButtonClicked();
    void SignalCloseButtonClicked();
    void SignalFloatingNotePanelButtonClicked();
private:
    friend class HugouView;
    QHBoxLayout* m_titleLayout;
    QPushButton* m_appIcon;
    QLabel* m_appName;
    QLabel* m_leftDragZone;
    QWidget* m_AIChatWidget;
    QHBoxLayout* m_AIChatWidgetLayout;
    QPushButton* m_AIChatIcon;
    QLineEdit* m_AIChatLineEdit;
    QLabel* m_rightDragZone;
    QWidget* m_userWidget;
    QHBoxLayout* m_userWidgetLayout;
    QPushButton* m_userButton;
    QPushButton* m_minimizeButton;
    QPushButton* m_scaleButton;
    QPushButton* m_closeButton;
    ButtonHoverWatcher* m_closeButtonHoverWatcher;
    //ButtonHoverWatcher* scaledButtonHoverWatcher;

    void setupUi();
    //void paintEvent(QPaintEvent* event) override;
};

QT_END_NAMESPACE