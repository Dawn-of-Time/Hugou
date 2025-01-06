#include "FloatingNotePanel.h"

FloatingNotePanel::FloatingNotePanel(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    this->setHidden(true);
    connect(ui.allFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(0); });
    connect(ui.successFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(1); });
    connect(ui.informationFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(2); });
    connect(ui.warningFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(3); });
    connect(ui.errorFloatingNoteButton, &QPushButton::clicked, [&]() {moveSlider(4); });

}

void FloatingNotePanel::moveSlider(int buttonIndex)
{
    ui.updateProperty(buttonIndex);
    this->setStyleSheet(this->styleSheet());

    QPropertyAnimation* animation = new QPropertyAnimation(ui.floatingNoteButtonSlider, "pos");
    int startX = ui.floatingNoteButtonSlider->x();
    int endX = ui.floatingNoteButtonList[buttonIndex]->x();
    animation->setDuration(abs(endX - startX));
    animation->setStartValue(QPoint(ui.floatingNoteButtonSlider->x(), 0));
    animation->setEndValue(QPoint(ui.floatingNoteButtonList[buttonIndex]->x(), 0));
    animation->setEasingCurve(QEasingCurve::OutQuint);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void FloatingNotePanel::blurOrClearBlurRequest()
{
    if (this->isHidden())
    {
        emit SignalBlurBackground();
    }
    else
    {
        emit SignalClearBackground();
    }
}

void FloatingNotePanel::switchPanel()
{
    this->updateUi();
    this->setHidden(!this->isHidden());
}

void FloatingNotePanel::updateUi()
{
    this->setGeometry(0, titleFrameHeight, this->parentWidget()->width(), this->parentWidget()->height() - titleFrameHeight);
    ui.floatingNoteButtonSlider->setFixedWidth(ui.allFloatingNoteButton->width());
}
