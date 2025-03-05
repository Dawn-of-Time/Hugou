#include "Assistance/Include/Assistance_DragFilter.h"

bool DragFilter::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QPushButton* button = qobject_cast<QPushButton*>(obj);
        if (button) {
            m_dragButton = button;
            m_dragStartPosition = static_cast<QMouseEvent*>(event)->pos();
        }
    }
    else if (event->type() == QEvent::MouseMove && m_dragButton) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() & Qt::LeftButton) {
            QPoint newPos = m_dragButton->pos() + mouseEvent->pos() - m_dragStartPosition;
            QWidget* parent = m_dragButton->parentWidget();
            newPos.setX(qMax(0, qMin(parent->width() - m_dragButton->width(), newPos.x())));
            newPos.setY(qMax(0, qMin(parent->height() - m_dragButton->height(), newPos.y())));
            m_dragButton->move(newPos);
            emit SignalPositionChanged(newPos);
        }
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        m_dragButton = nullptr;
    }
    return QObject::eventFilter(obj, event);
}