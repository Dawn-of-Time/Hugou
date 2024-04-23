#pragma once

#include "FloatingNote.h"
#include <list>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QGraphicsBlurEffect>
#include <QTimer>
#include <QQueue>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

class FloatingNoteManager :
	public QObject
{
	Q_OBJECT

public:
	FloatingNoteManager();
	~FloatingNoteManager();
	
	std::vector<FloatingNote*> floatingNoteShownList = {};
	std::vector<FloatingNote*> floatingNoteHiddenList = {};
	QQueue<FloatingNote*> createQueue;

	bool createFlag = true;
	
	void raiseFloatingNote(QWidget* HugouClass, FloatingNote::Type type, QString content); // 总调用创建。初始化消息（UI）。检测是否能执行动画
	void createFloatingNote(FloatingNote* floatingNote);  // 创建消息

	// 动画方法
	QPropertyAnimation* hideFloatingNote(FloatingNote* floatingNote, QPoint startValue, QPoint endValue);
	QPropertyAnimation* slideDownFloatingNote(int height);

signals:
	void SignalAnimationFinishedToTitleBar();

public slots:
	void checkCreateQueue();

protected slots:
	void SlotAnimationFinished();
	void dealLater(FloatingNote* floatingNote);
	void slideOutFloatingNote(FloatingNote* floatingNote);
};