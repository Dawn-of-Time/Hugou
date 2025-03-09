#pragma once
#include <QWidget>
#include <QStyleOption>
#include <QPainter>

class CloseWhenLeaveWidget :
    public QWidget
{
    Q_OBJECT

public:
    CloseWhenLeaveWidget(QWidget* parent = nullptr);

signals:
    void SignalClose();

private:
    void leaveEvent(QEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
};

