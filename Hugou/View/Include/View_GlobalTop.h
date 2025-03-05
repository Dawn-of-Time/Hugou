#pragma once
#include "Include/Const_Geometry.h"
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include <QQuickWidget>
#include <QStyleOption>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QQmlEngine>

class GlobalTopView
	: public QWidget 
{
	Q_OBJECT

public:
	bool m_isTopShown = false;
	GlobalTopView(QWidget* parent);
	~GlobalTopView();
	void fadeIn();
	void fadeOut();
	void setSource(const QString& filename);
	void setHint(const QString& hint);
	void removeSource();
	void updateUi(QWidget* Hugou);

signals:
	void fadeInFinished();
	void fadeOutFinished();
	void blurBackground();
	void clearBackground();

public slots:
	void switchTop();

private:
	QGraphicsOpacityEffect* m_effect;
	QVBoxLayout* m_globalTopLayout;
	QQuickWidget* m_globalTopQuickWidget;
	QLabel* m_globalTopHint;
	void setupUi();
	void paintEvent(QPaintEvent* event) {
		QWidget::paintEvent(event);
		QPainter painter(this);
		painter.fillRect(rect(), QColor(240, 242, 243, 255));
	}
};

