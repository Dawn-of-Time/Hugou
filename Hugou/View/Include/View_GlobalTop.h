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

class GlobalTopController;

class GlobalTopView
	: public QWidget 
{
	Q_OBJECT

public:
	struct ResourceBinding
	{
		QString qmlFileName;
		QString hint;
	};
	bool m_isTopShown = false;
	GlobalTopView(QWidget* parent);
	~GlobalTopView();
	void removeSource();
	void updateUi(QWidget* Hugou);
	void switchTop();
	void loadResourceBinding(ResourceBinding* binding);

signals:
	void SignalFadeInFinished();
	void SignalFadeOutFinished();

private:
	friend class GlobalTopController;
	ResourceBinding* m_binding = nullptr;
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
	void setSource(const QString& filename);
	void setHint(const QString& hint);
	void fadeIn();
	void fadeOut();
};

