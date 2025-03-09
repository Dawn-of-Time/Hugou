#pragma once
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include "Utils/Include/Utils_ButtonHoverWatcher.h"
#include <Windows.h>
#include <windowsx.h>
#include <dwmapi.h>

extern QWidget* globalHugou;

class PopupWidget :
    public QWidget
{
    Q_OBJECT

public:
    PopupWidget(const QString& title = "");
    ~PopupWidget();
    void setCentralWidget(QWidget* widget);

protected:
    QPushButton* m_closeButton;

private:
    QString m_title;
    QVBoxLayout* m_layout;
    QWidget* m_titleBar;
    QWidget* m_dragZone;
    QWidget* m_generalContent;
    ButtonHoverWatcher* m_closeButtonHoverWatcher;
    void setupUi();

    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
};