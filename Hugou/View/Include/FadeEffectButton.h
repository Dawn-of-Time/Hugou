#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsEffect>
#include <QLabel>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>

class FadeEffectButton :
	public QPushButton
{
	Q_OBJECT

public:
	FadeEffectButton(QWidget* parent);
	FadeEffectButton(QIcon icon, QSize iconSize, QString text, QFont font, QWidget* parent);
	FadeEffectButton(QIcon icon, QSize iconSize, QWidget* parent);
	FadeEffectButton(QString text, QFont font, QWidget* parent);

	QString text();
	void setIcon(QIcon icon);
	void setIconSize(QSize size);
	void setText(QString text);
	void setTextAlignment(Qt::Alignment alignment);
	void setFont(QFont font);
	inline void setStatus(bool isActive) { m_status = isActive; }
	void setFixedSize(int w, int h);
	void setFixedHeight(int h);
	void setBackgroundWidgetStyleSheet(QString styleSheet) { m_backgroundWidget->setStyleSheet(styleSheet); }
	QHBoxLayout* layout() { return m_buttonLayout; };

private:
	QHBoxLayout* m_buttonLayout = nullptr;
	QPushButton* m_iconZone = nullptr;
	QLabel* m_textZone = nullptr;
	QWidget* m_backgroundWidget;
	QGraphicsOpacityEffect* m_backgroundWidgetOpacityEffect;
	QPropertyAnimation* m_backgroundWidgetOpacityEffectAnimation;
	bool m_status = true;
	bool m_isMouseOver = false;

	void setGeneralLayout();
	void setGeneralStyle();
	void addTextZone(QString text, QFont font);
	void addIconZone(QIcon icon, QSize iconSize);
	void enableGraphicsEffect();
	void disableGraphicsEffect();
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
};

