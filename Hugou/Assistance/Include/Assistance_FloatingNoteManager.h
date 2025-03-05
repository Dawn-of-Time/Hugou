#pragma once

#include "View/Include/View_FloatingNote.h"
#include <list>
#include <QString>
#include <QStringList>
#include <QObject>
#include <QGraphicsBlurEffect>
#include <QTimer>
#include <QQueue>
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

	bool m_isAnimating = false;  // 提供给其它类，指示浮动消息管理器是否有动画正在播放。
	void raiseFloatingNote(FloatingNote::NoteType type, const QString& content, const QString& subcontent = ""); // 总调用创建。初始化消息（UI）。检测是否能执行动画
	void adjustFloatingNote();
	inline FloatingNote* getShownFloatingNote() { return m_shownFloatingNote; }
	inline FloatingNote* getLatestHiddenFloatingNote() { return m_hiddenFloatingNoteList.back(); }

public slots:
	void checkPopupQueue();

protected slots:
	void updatePointer();
	void deleteShownFloatingNote();
	void dealLater();
	void dealNow();

private:
	QWidget* m_hugou = nullptr;
	bool m_popupFlag = true;
	FloatingNote* m_forthcomingFloatingNote = nullptr;			// 即将展示的浮动消息。
	FloatingNote* m_shownFloatingNote = nullptr;					// 正在展示的浮动消息。
	std::vector<FloatingNote*> m_hiddenFloatingNoteList = {};		// 隐藏的浮动消息列表。
	FloatingNote* m_backupForthcomingFloatingNote = nullptr;		// 即将展示的浮动消息暂存，用于重新启用动画时回复状态。
	FloatingNote* m_backupShownFloatingNote = nullptr;		    // 正在展示的浮动消息暂存，用于重新启用动画时回复状态。
	QQueue<FloatingNote*> m_popupQueue;
	QParallelAnimationGroup* m_popupParallelGroup;
	QPropertyAnimation* m_dealLaterAnimation;
	QPropertyAnimation* m_dealNowAnimation;

	FloatingNoteManager();
	~FloatingNoteManager();
	void popupFloatingNote();
};