#pragma once

#include <QObject>
#include <QEvent>
#include <QComboBox>

class ComboboxWheelWatcher :
    public QObject
{
    Q_OBJECT

public:
    ComboboxWheelWatcher(QObject* obj);
    ~ComboboxWheelWatcher();
    bool eventFilter(QObject* obj, QEvent* event);
};

