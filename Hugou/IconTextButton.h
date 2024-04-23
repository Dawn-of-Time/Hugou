#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include "Const.h"

class IconTextButton :
	public QPushButton
{
public:
	QHBoxLayout* buttonLayout;
	QLabel* iconZone;
	QLabel* textZone;

	IconTextButton(QPixmap icon, QString text, QWidget* parent);
	void setIcon(QPixmap icon) 
	{
		icon = icon.scaled(QSize(18, 18), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		iconZone->setPixmap(icon);
	};

	void setText(QString text)
	{
		textZone->setText(text);
		textZone->setFont(asideFont);
	}
};

