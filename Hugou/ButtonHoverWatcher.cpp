#include "ButtonHoverWatcher.h"

ButtonHoverWatcher::ButtonHoverWatcher(QString default_res, QString hover_res, QObject* parent) :
    QObject(parent)
{
    this->default_res = default_res;
    this->hover_res = hover_res;
}

ButtonHoverWatcher::ButtonHoverWatcher(QLabel* backgroundLabel, QString default_color, QString hover_color, QObject* parent)
{
    this->backgroundLabel = backgroundLabel;
    this->default_color = default_color;
    this->hover_color = hover_color;
}

ButtonHoverWatcher::ButtonHoverWatcher(QString default_res, QString hover_res, 
    QLabel* backgroundLabel, QString default_color, QString hover_color, QObject* parent)
{
    this->default_res = default_res;
    this->hover_res = hover_res;
    this->backgroundLabel = backgroundLabel;
    this->default_color = default_color;
    this->hover_color = hover_color;
}

ButtonHoverWatcher::ButtonHoverWatcher(QPoint startPos, QPoint endPos, Direction direction, QObject* parent)
{
    this->startPos = startPos;
    this->endPos = endPos;
    this->direction = direction;
}

ButtonHoverWatcher::~ButtonHoverWatcher()
{}

bool ButtonHoverWatcher::eventFilter(QObject* watched, QEvent* event)
{
    QPushButton* button = qobject_cast<QPushButton*>(watched); // 转换为按钮类型
    if (!button) {
        return false;
    }

    if (event->type() == QEvent::Enter) {
        if (!hover_res.isEmpty()) button->setIcon(QIcon(this->hover_res));
        if (backgroundLabel && (!hover_color.isEmpty()))
        {
            backgroundLabel->setStyleSheet(QString("QLabel#" + backgroundLabel->objectName() + " {background-color: %1}").arg(hover_color));
        }
        if ((!startPos.isNull()) && (!endPos.isNull()))
        {
            QPropertyAnimation* animation = new QPropertyAnimation(button, "pos");
            QPoint currentPos = button->pos();
            animation->setStartValue(currentPos);
            animation->setEndValue(endPos);
            if (direction == Direction::Horizontal) animation->setDuration(20 * abs(currentPos.x() - endPos.x()));
            else animation->setDuration(20 * abs(currentPos.y() - endPos.y()));
            animation->start(QPropertyAnimation::DeleteWhenStopped);
        }
        return true;
    }

    if (event->type() == QEvent::Leave) {
        if (!default_res.isEmpty())  button->setIcon(QIcon(this->default_res));
        if (backgroundLabel && (!default_color.isEmpty())) backgroundLabel->setStyleSheet(QString("QLabel {background-color: %1}").arg(default_color));
        if ((!startPos.isNull()) && (!endPos.isNull()))
        {
            QPropertyAnimation* animation = new QPropertyAnimation(button, "pos");
            QPoint currentPos = button->pos();
            animation->setStartValue(currentPos);
            animation->setEndValue(startPos);
            if (direction == Direction::Horizontal) animation->setDuration(20 * abs(currentPos.x() - startPos.x()));
            else animation->setDuration(20 * abs(currentPos.y() - startPos.y()));
            animation->start(QPropertyAnimation::DeleteWhenStopped);
        }
        return true;
    }

    return false;
}

void ButtonHoverWatcher::setResource(QString default_res, QString hover_res)
{
    this->default_res = default_res;
    this->hover_res = hover_res;
}
