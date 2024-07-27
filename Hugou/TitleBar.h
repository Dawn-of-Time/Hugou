#pragma once

#include <QWidget>
#include <QParallelAnimationGroup>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMouseEvent>
#include "ui_TitleBar.h"

class TitleBar :
	public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget* parent);

	QQmlApplicationEngine engine;
	QWidget* mainWindow;
	FloatingNotePanel* floatingNotePanel;
	

signals:
	void SignalRestore();
	void SignalMaximize();
	void SignalBlurStackedWidget();
	void SignalClearStackedWidget();

protected slots:
	void minimize();
	void scale();
	void slideFloatingNotePoint();
	void floatFloatingNotePoint();
	void allocateFloatingNotePoint();

private:
	Ui_TitleBar ui;
	QPoint distance;
	int screenWidth;
	int screenHeight;
	QRect generalGeometry;
	QRect maximumGeometry;

	void mousePressEvent(QMouseEvent* event) override
	{
		distance = event->globalPos() - mainWindow->pos();
		qDebug() << mainWindow->size();
		qDebug() << this->size();
	}

	void mouseMoveEvent(QMouseEvent* event) override
	{
		if (ui.dragZone->underMouse()) {
			mainWindow->move(event->globalPos() - distance);
		}
	}
};

