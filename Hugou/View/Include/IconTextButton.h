#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsEffect>
#include <QLabel>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>
#include "Var.h"
#include "Const_Geometry.h"

class IconTextButton :
	public QPushButton
{
	Q_OBJECT

public:
	IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent);

	void setIcon(QPixmap icon);
	void setIconSize(QSize size);
	void setText(QString text, QFont font);
	inline void setStatus(bool isActive) { m_status = isActive; }
	void setFixedSize(int w, int h);
	void setFixedHeight(int h);
	void setBackgroundWidgetStyleSheet(QString styleSheet) { m_backgroundWidget->setStyleSheet(styleSheet); }

private:
	QHBoxLayout* m_buttonLayout;
	QLabel* m_iconZone;
	QLabel* m_textZone;
	QWidget* m_backgroundWidget;
	QGraphicsOpacityEffect* m_backgroundWidgetOpacityEffect;
	QPropertyAnimation* m_backgroundWidgetOpacityEffectAnimation;
	bool m_status = true;

	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
};

