#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Widgets/Include/Menu/MenuItem.h"
#include "Utils/Include/Utils_ButtonHoverWatcher.h"
#include <Windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <dwmapi.h>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>

class MenuItem;

class Menu :
    public QWidget
{
    Q_OBJECT

public:
    Menu(QWidget* parent = nullptr);
    ~Menu();
    void addMenuItem(MenuItem* item);

signals:
    void SignalSaved(QMap<QString, QString> resultMap);

private:
    void setupUi();
    QVBoxLayout* m_layout;
    QWidget* m_titleBar;
    QLabel* m_icon;
    QWidget* m_dragZone;
    QPushButton* m_saveButton;
    QWidget* m_centralWidget;
    QVBoxLayout* m_centralWidgetLayout;
    //ButtonHoverWatcher* m_closeButtonHoverWatcher;

    bool event(QEvent* event) override;
    bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override;
    void paintEvent(QPaintEvent* event) override;
    void save();
};

