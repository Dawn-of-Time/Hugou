#pragma once

#include "FloatingNote.h"
#include <list>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QGraphicsBlurEffect>
#include <QTimer>
#include <QQueue>
#include <QMutex> 
#include <QAnimationGroup>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

class FloatingNoteManager :
	public QObject
{
	Q_OBJECT

public:
	static FloatingNoteManager* getManager();
	void setHugou(QWidget* hugou) { m_hugou = hugou; }

	bool isAnimating = false;  // 提供给其它类，指示浮动消息管理器是否有动画正在播放。
	void raiseFloatingNote(FloatingNote::Type type, QString content, QString subcontent = ""); // 总调用创建。初始化消息（UI）。检测是否能执行动画
	void adjustFloatingNote();
	inline FloatingNote* getShownFloatingNote() { return shownFloatingNote; }
	inline FloatingNote* getLatestHiddenFloatingNote() { return hiddenFloatingNoteList.back(); }

signals:
	void SignalAnimationFinishedToTitleBar();

public slots:
	void checkPopupQueue();

protected slots:
	void sendToPanel();
	void deleteShownFloatingNote();
	void dealLater();
	void dealNow();

private:
	static FloatingNoteManager* m_manager;
	static QMutex m_mutex;
	QWidget* m_hugou = nullptr;
	bool popupFlag = true;
	FloatingNote* forthcomingFloatingNote = nullptr;			// 即将展示的浮动消息。
	FloatingNote* shownFloatingNote = nullptr;					// 正在展示的浮动消息。
	std::vector<FloatingNote*> hiddenFloatingNoteList = {};		// 隐藏的浮动消息列表。
	FloatingNote* backupForthcomingFloatingNote = nullptr;		// 即将展示的浮动消息暂存，用于重新启用动画时回复状态。
	FloatingNote* backupShownFloatingNote = nullptr;		    // 正在展示的浮动消息暂存，用于重新启用动画时回复状态。
	QQueue<FloatingNote*> popupQueue;
	QParallelAnimationGroup* popupParallelGroup;
	QPropertyAnimation* dealLaterAnimation;
	QPropertyAnimation* dealNowAnimation;

	FloatingNoteManager();
	~FloatingNoteManager();
	void popupFloatingNote();
};