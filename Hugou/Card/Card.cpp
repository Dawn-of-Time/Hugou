#include "Card/Include/Card.h"

Card::Card(QWidget* parent)
	:QWidget(parent)
{
	setFixedWidth(300);
	setObjectName("card");
	setStyleSheet("QWidget #card {border-radius: 10px; background-color: white}");
}