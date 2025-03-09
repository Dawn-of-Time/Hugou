#pragma once
#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>

class DragFilter :
    public QObject
{
    Q_OBJECT

public:
    DragFilter(QWidget* parent = nullptr) : QObject(parent) {};

signals:
    void SignalPositionChanged(const QPoint& pos);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QPushButton* m_dragButton = nullptr;
    QPoint m_dragStartPosition;
};

