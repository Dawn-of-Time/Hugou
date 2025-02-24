#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Assistance_ButtonHoverWatcher.h"
#include "Const_Geometry.h"
#include <Windows.h>
#include <windowsx.h>
#include <dwmapi.h>

class PopupWidget :
    public QWidget
{
    Q_OBJECT

public:
    PopupWidget(QString title = "", QWidget* parent = nullptr);
    ~PopupWidget();
    void setCentralWidget(QWidget* widget);

private:
    QString m_title;
    QVBoxLayout* m_layout;
    QWidget* m_titleBar;
    QWidget* m_dragZone;
    QPushButton* m_closeButton;
    QWidget* m_generalContent;
    ButtonHoverWatcher* m_closeButtonHoverWatcher;
    void setupUi();

    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
};