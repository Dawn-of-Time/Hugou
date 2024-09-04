#pragma once
#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "ui_GlobalTop.h"

class GlobalTop
	: public QWidget 
{
	Q_OBJECT

public:
	bool isTopShown = false;
	GlobalTop(QWidget* parent);
	void fadeIn();
	void fadeOut();
	void setSource(QString filename);
	void setHint(QString hint);
	void removeSource();
	void updateUi(QWidget* Hugou);

signals:
	void fadeInFinished();
	void blurBackground();
	void clearBackground();

public slots:
	void switchTop();

private:
	Ui_GlobalTop ui;
	QGraphicsOpacityEffect* effect;
	QWidget* mainWindow;
	QColor color = QColor(240, 242, 243, 255);
	void paintEvent(QPaintEvent* event) {
		QWidget::paintEvent(event);
		QPainter painter(this);
		painter.fillRect(rect(), color);
	}
};

