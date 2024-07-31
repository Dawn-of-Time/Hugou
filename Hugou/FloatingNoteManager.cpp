#include "FloatingNoteManager.h"

FloatingNoteManager::FloatingNoteManager() :
    QObject()
{
    popupParallelGroup = new QParallelAnimationGroup;
    dealLaterAnimation = new QPropertyAnimation;
    dealNowAnimation = new QPropertyAnimation;
}

FloatingNoteManager::~FloatingNoteManager()
{}

void FloatingNoteManager::raiseFloatingNote(QWidget* HugouClass, FloatingNote::Type type, QString content)
{
    // 生成浮动消息
    FloatingNote* floatingNote = new FloatingNote(HugouClass);
    floatingNote->setType(type);
    floatingNote->setContent(content);
    floatingNote->updateUI(); 
    floatingNote->raise();
    // 弹出动画。动画过程不允许打断
    if (!popupFlag) popupQueue.append(floatingNote); // 等待弹出
    else
    {
        popupFlag = false;
        forthcomingFloatingNote = floatingNote;
        //qDebug() << "[POP] From Start";
        popupFloatingNote();
    }
}

void FloatingNoteManager::popupFloatingNote()
{
    isAnimating = true;
    // 备份，以便回复。
    backupForthcomingFloatingNote = forthcomingFloatingNote;
    backupShownFloatingNote = shownFloatingNote;

    popupParallelGroup->clear();
    forthcomingFloatingNote->show();
    QPropertyAnimation* raiseAnimation = forthcomingFloatingNote->raiseNote();
    popupParallelGroup->addAnimation(raiseAnimation);
    // 如果已经有消息，那么前面的消息移出并隐藏，同时标题栏按钮执行动画；如果有消息正在执行动画，先等待
    if (shownFloatingNote)
    {
        //qDebug() << "[BLOCK] => sendToPanel";
        // 将前面的消息隐藏，动画结束后将这个消息发送到消息中心面板。
        QPropertyAnimation* hideAnimation = shownFloatingNote->dropNote();
        popupParallelGroup->addAnimation(hideAnimation);
        popupParallelGroup->disconnect();
        connect(popupParallelGroup, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::sendToPanel);
    }
    // 如果没有消息，动画结束后将弹出标志复位，同时检查序列中有无后续事件（无需消息点操作）
    else 
    {
        //qDebug() << "[BLOCK] => checkPopupQueue";
        shownFloatingNote = forthcomingFloatingNote;
        forthcomingFloatingNote = nullptr;
        popupParallelGroup->disconnect();
        connect(popupParallelGroup, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::checkPopupQueue);
    }
    popupParallelGroup->start();
}

void FloatingNoteManager::adjustFloatingNote(QWidget* Hugou)
{
    // 意外情况发生时（例如在动画播放期间变化窗口），结束动画的位置并不符合预期，需要强制打断动画，重新计算结束位置，
    // 然后重新开始动画。一旦有任何调整窗口的行为，就将触发这个过程。
    QPoint floatingNoteHiddenPos = QPoint(Hugou->width(), titleFrameHeight);
    QPoint floatingNoteShownPos = QPoint(Hugou->width() - floatingNoteWidth - 20, titleFrameHeight);
    if (shownFloatingNote)
    {
        shownFloatingNote->setShownPos(floatingNoteShownPos);
        shownFloatingNote->setHiddenPos(floatingNoteHiddenPos);
    }
    if (forthcomingFloatingNote)
    {
        forthcomingFloatingNote->setShownPos(floatingNoteShownPos);
        forthcomingFloatingNote->setHiddenPos(floatingNoteHiddenPos);
    }
    if (!popupQueue.empty())
    {
        for (FloatingNote* floatingNote : popupQueue)
        {
            floatingNote->setShownPos(floatingNoteShownPos);
            floatingNote->setHiddenPos(floatingNoteHiddenPos);
            floatingNote->move(floatingNoteHiddenPos);
        }
    }
    if (dealLaterAnimation->state() == QPropertyAnimation::Running)
    {
        //qDebug() << "Status1";
        dealLaterAnimation->stop();
        dealLater();
    }
    if (dealNowAnimation->state() == QPropertyAnimation::Running)
    {
        //qDebug() << "Status2";
        dealNowAnimation->stop();
        dealNow();
    }
    if (popupParallelGroup->state() == QParallelAnimationGroup::Running)
    {
        //qDebug() << "Status3";
        popupParallelGroup->stop();
        forthcomingFloatingNote = backupForthcomingFloatingNote;
        shownFloatingNote = backupShownFloatingNote;
        //qDebug() << "[POP] From Status3";
        popupFloatingNote();
    }
    // 存在一种特殊情况。当大量消息涌入时，在消息更替的间隙，所有动画也是停滞状态。因此，当
    // 没有动画启动并且popupQueue.empty()时，才是真正的停止。
    if (dealLaterAnimation->state() == QPropertyAnimation::Stopped
        && dealNowAnimation->state() == QPropertyAnimation::Stopped
        && popupParallelGroup->state() == QParallelAnimationGroup::Stopped
        && popupQueue.empty())
    {
        //qDebug() << "Status4";
        forthcomingFloatingNote = backupForthcomingFloatingNote;
        shownFloatingNote = nullptr;
        popupFlag = false;
        //qDebug() << "[POP] From Status4";
        popupFloatingNote();
    }
}


// 槽函数
void FloatingNoteManager::sendToPanel()
{
    // 隐藏已经完成动画的（原来正在展示的）浮动消息，并向隐藏列表末尾添加这个浮动消息。
    // 然后将已经完成动画的（原来即将展示的）浮动消息用指针shownFloatingNote指向。
    // 接着重置指针forthcomingFloatingNote。最后向标题栏发送信号，引导相应动画。
    isAnimating = false;
    shownFloatingNote->hide();
    hiddenFloatingNoteList.push_back(shownFloatingNote);
    shownFloatingNote = forthcomingFloatingNote;
    forthcomingFloatingNote = nullptr;
    emit SignalAnimationFinishedToTitleBar();
}

void FloatingNoteManager::deleteShownFloatingNote()
{
    isAnimating = false;
    shownFloatingNote->hide();
    shownFloatingNote->setParent(nullptr);
    delete shownFloatingNote;
    shownFloatingNote = forthcomingFloatingNote;
    forthcomingFloatingNote = nullptr;
    checkPopupQueue();
}

void FloatingNoteManager::checkPopupQueue()
{
    popupFlag = true;
    isAnimating = false;
    if (!popupQueue.empty())
    {
        popupFlag = false;
        forthcomingFloatingNote = popupQueue.dequeue();
        //qDebug() << "[POP] From popupQueue";
        popupFloatingNote();
    }
    else
    {
        if (shownFloatingNote)
        {
            shownFloatingNote->setEnabled(true);
            connect(shownFloatingNote, &FloatingNote::SignalDealLater, this, &FloatingNoteManager::dealLater);
            connect(shownFloatingNote, &FloatingNote::SignalDealNow, this, &FloatingNoteManager::dealNow);
        }
    }
}

void FloatingNoteManager::dealLater()
{
    isAnimating = true;
    dealLaterAnimation = shownFloatingNote->dropNote();
    connect(dealLaterAnimation, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::sendToPanel);
    dealLaterAnimation->start();
}

void FloatingNoteManager::dealNow()
{
    isAnimating = true;
    dealNowAnimation = shownFloatingNote->dropNote();
    connect(dealNowAnimation, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::deleteShownFloatingNote);
    dealNowAnimation->start();
}