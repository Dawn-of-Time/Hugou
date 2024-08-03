#include "FloatingNotePanel.h"

FloatingNotePanel::FloatingNotePanel(QWidget* parent) :
	QLabel(parent)
{
	ui.setupUi(this);
}

void FloatingNotePanel::blurOrClearBlurRequest()
{
    if (!isPanelShown)
    {
        emit blurBackground();
    }
    else
    {
        emit clearBackground();
    }
}

void FloatingNotePanel::switchPanel()
{
    if (!isPanelShown)
    {
        this->setHidden(false);
        isPanelShown = true;
    }
    else
    {
        this->setHidden(true);
        isPanelShown = false;
    }
}

void FloatingNotePanel::updateUi(QWidget* Hugou)
{
    this->setGeometry(0, titleFrameHeight, Hugou->width(), Hugou->height() - titleFrameHeight);
}