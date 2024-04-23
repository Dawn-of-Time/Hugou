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

	bool isMaximum = false;
	QQmlApplicationEngine engine;
	QWidget* parent;
	FloatingNotePanel* floatingNotePanel;
	QPoint mousePos;

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

signals:
	void SignalRestore();
	void SignalMaximize();
	void SignalBlurStackedWidget();
	void SignalClearStackedWidget();

protected slots:
	void minimize();
	void scaled();
	void slideFloatingNotePoint();
	void floatFloatingNotePoint();
	void allocateFloatingNotePoint();

private:
	Ui_TitleBar ui;
};

