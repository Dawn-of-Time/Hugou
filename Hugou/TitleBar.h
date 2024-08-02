#pragma once

#include <QWidget>
#include <QParallelAnimationGroup>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMouseEvent>
#include <Windows.h>
#include "ui_TitleBar.h"

class Hugou;

class TitleBar :
	public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget* parent);

	QQmlApplicationEngine engine;
	QWidget* mainWindow;
	FloatingNotePanel* floatingNotePanel;
	
	bool isOnMaxButton(QPoint windowPos);
	bool isOnDragZone(QPoint windowPos);

signals:
	void SignalBlur();
	void SignalClearBlur();

protected slots:
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
	friend class Hugou;

	void mouseDoubleClickEvent(QMouseEvent* event) { scale(); }
};

