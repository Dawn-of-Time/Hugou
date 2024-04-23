#include "ComboboxWheelWatcher.h"

ComboboxWheelWatcher::ComboboxWheelWatcher(QObject* obj) :
    QObject(obj)
{}

ComboboxWheelWatcher::~ComboboxWheelWatcher()
{}

bool ComboboxWheelWatcher::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::Wheel && obj->inherits("QComboBox"))
    {
        return true;
    }
    return false;
}