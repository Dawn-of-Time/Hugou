#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "Const.h"

class IconTextButton :
	public QPushButton
{
	Q_OBJECT

public:
	QHBoxLayout* buttonLayout;
	QLabel* iconZone;
	QLabel* textZone;

	IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent);

	void setIcon(QPixmap icon, QSize size) 
	{
		icon = icon.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		iconZone->setPixmap(icon);
	};

	void setText(QString text, QFont font)
	{
		textZone->setText(text);
		textZone->setFont(font);
	}
};

