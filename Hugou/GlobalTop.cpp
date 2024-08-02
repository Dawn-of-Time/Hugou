#include "GlobalTop.h"

GlobalTop::GlobalTop(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
}

void GlobalTop::updateUi(QWidget* Hugou)
{
    this->setGeometry(0, 0, Hugou->width(), Hugou->height());
}