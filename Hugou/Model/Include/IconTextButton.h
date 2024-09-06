#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

class IconTextButton :
	public QPushButton
{
	Q_OBJECT

public:
	IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent);

	void setIcon(QPixmap icon, QSize size) 
	{
		//icon = icon.scaled(size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		iconZone->setPixmap(icon);
	};

	void setText(QString text, QFont font)
	{
		textZone->setText(text);
		textZone->setFont(font);
	}

private:
	QMap<QString, QString> buttonStatusMap;
	QHBoxLayout* buttonLayout;
	QLabel* iconZone;
	QLabel* textZone;
};

