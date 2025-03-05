#include "View/Include/CloseWhenLeaveWidget.h"

CloseWhenLeaveWidget::CloseWhenLeaveWidget(QWidget* parent)
	:QWidget(parent)
{
}

void CloseWhenLeaveWidget::leaveEvent(QEvent* event) {
    this->close();
    QWidget::leaveEvent(event);
}

void CloseWhenLeaveWidget::closeEvent(QCloseEvent* event)
{
    emit SignalClose();
    QWidget::closeEvent(event);
}

void CloseWhenLeaveWidget::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}