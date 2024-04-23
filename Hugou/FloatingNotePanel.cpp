#include "FloatingNotePanel.h"

FloatingNotePanel::FloatingNotePanel(QWidget* parent) :
	QLabel(parent)
{
	ui.setupUi(this);
}

void FloatingNotePanel::showPanel()
{
    if (!isPanelShown)
    {
        emit blurBackground();
        this->setHidden(false);
        isPanelShown = true;
    }
    else
    {
        emit clearBackground();
        this->setHidden(true);
        isPanelShown = false;
    }
}