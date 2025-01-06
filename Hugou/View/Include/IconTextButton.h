#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsEffect>
#include <QLabel>
#include <QPropertyAnimation>
#include "Var.h"
#include "Const_Geometry.h"

class IconTextButton :
	public QPushButton
{
	Q_OBJECT

public:
	IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent);

	void setIcon(QPixmap icon) 
	{
		icon.setDevicePixelRatio(getScale());
		m_iconZone->setPixmap(icon);
	};

	void setText(QString text, QFont font)
	{
		m_textZone->setText(text);
		m_textZone->setFont(font);
	}

	void setStatus(bool isActive) { m_status = isActive; }

private:
	QHBoxLayout* m_buttonLayout;
	QLabel* m_iconZone;
	QLabel* m_textZone;
	QWidget* m_backgroundWidget;
	QGraphicsOpacityEffect* m_backgroundWidgetOpacityEffect;
	QPropertyAnimation* m_backgroundWidgetOpacityEffectAnimation;
	bool m_status = false;

	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
};

