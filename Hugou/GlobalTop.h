#pragma once
#include <QWidget>
#include "ui_GlobalTop.h"

class GlobalTop
	: public QWidget 
{
	Q_OBJECT

public:
	bool isTopShown = false;
	GlobalTop(QWidget* parent);
	void blurOrClearBlurRequest();
	void setSource(QUrl url);
	void setHint(QString hint);
	void removeSource();
	void updateUi(QWidget* Hugou);

signals:
	void blurBackground();
	void clearBackground();

public slots:
	void switchTop();

private:
	Ui_GlobalTop ui;
};

