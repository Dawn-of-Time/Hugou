#pragma once
#include "Const.h"
#include <QLabel>
#include <QFile>
#include <QVBoxLayout>
#include <QQuickWidget>
#include <QStyleOption>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

class GlobalTopView
	: public QWidget 
{
	Q_OBJECT

public:
	bool isTopShown = false;
	GlobalTopView(QWidget* parent);
	void fadeIn();
	void fadeOut();
	void setSource(QString filename);
	void setHint(QString hint);
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

