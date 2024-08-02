#pragma once
#include <QWidget>
#include "ui_GlobalTop.h"

class GlobalTop
	: public QWidget 
{
	Q_OBJECT

public:
	bool isShown = false;
	GlobalTop(QWidget* parent);
	void updateUi(QWidget* Hugou);

signals:
	void blurBackground();
	void clearBackground();

public slots:
	void showTop();

private:
	Ui_GlobalTop ui;
};

