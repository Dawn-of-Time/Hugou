#include "FloatingNoteManager.h"

FloatingNoteManager::FloatingNoteManager() :
    QObject()
{}

FloatingNoteManager::~FloatingNoteManager()
{}

void FloatingNoteManager::raiseFloatingNote(QWidget* HugouClass, FloatingNote::Type type, QString content)
{
    FloatingNote* floatingNote = new FloatingNote(HugouClass);
    floatingNote->setType(type);
    floatingNote->setContent(content);
    floatingNote->updateUI(); 
    floatingNote->raise();
    // 动画过程不允许打断
    if (!createFlag) createQueue.append(floatingNote);
    else createFloatingNote(floatingNote);
}

void FloatingNoteManager::createFloatingNote(FloatingNote* floatingNote)
{
    createFlag = false;
    floatingNote->show();
    floatingNoteShownList.push_back(floatingNote);
    QParallelAnimationGroup* parallelGroup = new QParallelAnimationGroup;
    parallelGroup->addAnimation(floatingNote->raiseNote());
    // 在接下来的过程中，所有消息不可响应
    for (int i = 0; i < floatingNoteShownList.size(); i++)
        floatingNoteShownList[i]->setEnabled(false);
    // 隐藏消息到消息中心的两种情况：
    // 1. 展示消息冲突时
    // 如果已经有消息，那么前面的消息下移并移出、隐藏，同时标题栏按钮执行动画；如果有消息正在执行动画，先等待
    if (floatingNoteShownList.size() > 1) 
    {
        floatingNoteHiddenList.push_back(floatingNoteShownList[0]);
        floatingNoteShownList.erase(std::remove(floatingNoteShownList.begin(), floatingNoteShownList.end(), floatingNoteShownList[0]), floatingNoteShownList.end());
        QSequentialAnimationGroup* sequentialGroup = new QSequentialAnimationGroup;
        // 下移动画。将前面的消息下移新消息的高度+10
        sequentialGroup->addAnimation(slideDownFloatingNote(floatingNote->height()));
        // 隐藏动画。将前面的消息隐藏
        sequentialGroup->addAnimation(hideFloatingNote(
            floatingNoteHiddenList.back(),
            QPoint(floatingNoteHiddenList.back()->x(), floatingNoteHiddenList.back()->y() + floatingNote->height() + 5),
            QPoint(floatingNoteHiddenList.back()->x() + floatingNoteHiddenList.back()->width() + 10, floatingNoteHiddenList.back()->y() + floatingNote->height() + 5)));
        parallelGroup->disconnect();
        connect(parallelGroup, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::SlotAnimationFinished);
        parallelGroup->addAnimation(sequentialGroup);
    }
    // 如果没有消息，动画结束后将创建标志复位，同时检查序列中有无后续事件（无需消息点操作）
    else 
    {
        parallelGroup->disconnect();
        connect(parallelGroup, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::checkCreateQueue);
    }
    parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);

    // 2. 稍后处理时
    connect(floatingNote, &FloatingNote::SignalDealLater, this, &FloatingNoteManager::dealLater);

    connect(floatingNote, &FloatingNote::SignalDealNow, this, &FloatingNoteManager::slideOutFloatingNote);
}

QPropertyAnimation* FloatingNoteManager::hideFloatingNote(FloatingNote* floatingNote, QPoint startValue, QPoint endValue)
{
    floatingNote->isShown = false;
    return floatingNote->dropNote(startValue, endValue);
}

QPropertyAnimation* FloatingNoteManager::slideDownFloatingNote(int height)
{
    QPropertyAnimation* animation = new QPropertyAnimation(floatingNoteHiddenList.back(), "pos");
    animation->setDuration(500);
    animation->setStartValue(floatingNoteHiddenList.back()->pos());
    animation->setEndValue(QPoint(floatingNoteHiddenList.back()->x(), floatingNoteHiddenList.back()->y() + height + 5));
    animation->setEasingCurve(QEasingCurve::OutQuint);
    return animation;
}

// 槽函数
void FloatingNoteManager::SlotAnimationFinished()
{
    emit SignalAnimationFinishedToTitleBar();
}

void FloatingNoteManager::slideOutFloatingNote(FloatingNote* floatingNote)
{
    if (floatingNote->isShown) floatingNoteShownList.erase(std::remove(floatingNoteShownList.begin(), floatingNoteShownList.end(), floatingNote), floatingNoteShownList.end());
    else floatingNoteHiddenList.erase(std::remove(floatingNoteHiddenList.begin(), floatingNoteHiddenList.end(), floatingNote), floatingNoteHiddenList.end());
    QPropertyAnimation* animation = floatingNote->dropNote(floatingNote->pos(), QPoint(floatingNote->x() + floatingNote->width() + 10, floatingNote->y()));
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void FloatingNoteManager::checkCreateQueue()
{
    createFlag = true;
    if (createQueue.size() != 0)
    {
        createFloatingNote(createQueue.dequeue());
    }
    else
        if (!floatingNoteShownList.empty()) floatingNoteShownList[0]->setEnabled(true);
}

void FloatingNoteManager::dealLater(FloatingNote* floatingNote)
{
    floatingNoteHiddenList.push_back(floatingNoteShownList[0]);
    floatingNoteShownList.erase(std::remove(floatingNoteShownList.begin(), floatingNoteShownList.end(), floatingNoteShownList[0]), floatingNoteShownList.end());
    QSequentialAnimationGroup* sequentialDealLaterGroup = new QSequentialAnimationGroup;
    sequentialDealLaterGroup->addAnimation(hideFloatingNote(
        floatingNote,
        QPoint(floatingNote->x(), floatingNote->y()),
        QPoint(floatingNote->x() + floatingNote->width() + 10, floatingNote->y())));
    connect(sequentialDealLaterGroup, &QSequentialAnimationGroup::finished, this, &FloatingNoteManager::SlotAnimationFinished);
    sequentialDealLaterGroup->start(QSequentialAnimationGroup::DeleteWhenStopped);
}