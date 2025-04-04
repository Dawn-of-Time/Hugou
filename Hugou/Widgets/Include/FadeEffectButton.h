#pragma once

#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsEffect>
#include <QLabel>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>
#include <QPainterPath>

class FadeEffectButton :
	public QPushButton
{
	Q_OBJECT

public:
	FadeEffectButton(QWidget* parent);
	FadeEffectButton(const QIcon& icon, const QSize& iconSize, const QString& text, const QFont& font, QWidget* parent);
	FadeEffectButton(const QIcon& icon, const QSize& iconSize, QWidget* parent);
	FadeEffectButton(const QString& text, const QFont& font, QWidget* parent);

	QString text();
	void setIcon(const QIcon& icon);
	void setIconSize(const QSize& size);
	void setText(const QString& text);
	void setTextAlignment(Qt::Alignment alignment);
	void setFont(const QFont& font);
	inline void setStatus(bool isActive) { m_status = isActive; }
	void setFixedSize(int w, int h);
	void setFixedHeight(int h);
	void setBackgroundWidgetStyleSheet(QString styleSheet) { m_backgroundWidget->setStyleSheet(styleSheet); }
	void setContentsMargins(int left, int top, int right, int bottom);
	void setGradient(QGradient gradient) { m_hasGradient = true; m_gradient = gradient; };
	void setPainterPath(QPainterPath painterPath) { m_hasPainterPath = true; m_painterPath = painterPath; };
	void setTextColor(const QColor& color);
	void setBaseColor(const QColor& color) { m_baseColor = color; };

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
	bool m_hasGradient = false;
	bool m_hasPainterPath = false;
	QGradient m_gradient;
	QPainterPath m_painterPath;
	QColor m_textColor = Qt::black;
	QColor m_baseColor = Qt::transparent;

	void setGeneralLayout();
	void setGeneralStyle();
	void addTextZone(const QString& text, const QFont& font);
	void addIconZone(const QIcon& icon, const QSize& iconSize);
	void enableGraphicsEffect();
	void disableGraphicsEffect();
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void showEvent(QShowEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
};

