#include "IconTextButtonHoverWatcher.h"

IconTextButtonHoverWatcher::IconTextButtonHoverWatcher(QString default_res, QString hover_res, QSize iconSize, QObject* parent) :
    QObject(parent)
{
    this->default_res = default_res;
    this->hover_res = hover_res;
    this->iconSize = iconSize;
}

bool IconTextButtonHoverWatcher::eventFilter(QObject* watched, QEvent* event)
{
    IconTextButton* button = qobject_cast<IconTextButton*>(watched); // 转换为按钮类型
    if (!button) {
        return false;
    }

    if (event->type() == QEvent::Enter) {
        if (!hover_res.isEmpty())
        {
            button->setIcon(QPixmap(this->hover_res));
            return true;
        }
    }

    if (event->type() == QEvent::Leave) {
        if (!default_res.isEmpty())
        {
            button->setIcon(QPixmap(this->default_res));
            return true;
        }
    }
    return false;
}