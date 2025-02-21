#include "Assistance_FloatingNoteManager.h"

FloatingNoteManager::FloatingNoteManager() :
    QObject()
{
    m_popupParallelGroup = new QParallelAnimationGroup;
    m_dealLaterAnimation = new QPropertyAnimation;
    m_dealNowAnimation = new QPropertyAnimation;
}

FloatingNoteManager::~FloatingNoteManager()
{
    m_popupParallelGroup->clear();
    delete m_popupParallelGroup;
    delete m_dealLaterAnimation;
    delete m_dealNowAnimation;
}

FloatingNoteManager* FloatingNoteManager::getManager()
{
    static FloatingNoteManager manager;
    return &manager;
}

void FloatingNoteManager::raiseFloatingNote(FloatingNote::Type type, QString content, QString subcontent)
{
    // 生成浮动消息
    FloatingNote* floatingNote = new FloatingNote(m_hugou);
    floatingNote->setType(type);
    floatingNote->setContent(content);
    if (!subcontent.isEmpty()) floatingNote->setSubcontent(subcontent);
    floatingNote->updateUI(); 
    floatingNote->raise();
    // 弹出动画。动画过程不允许打断
    if (!m_popupFlag) m_popupQueue.append(floatingNote); // 等待弹出
    else
    {
        m_popupFlag = false;
        m_forthcomingFloatingNote = floatingNote;
        //qDebug() << "[POP] From Start";
        popupFloatingNote();
    }
}

void FloatingNoteManager::popupFloatingNote()
{
    m_isAnimating = true;
    m_popupParallelGroup->clear();

    // 备份，以便回复。
    m_backupForthcomingFloatingNote = m_forthcomingFloatingNote;
    m_backupShownFloatingNote = m_shownFloatingNote;

    m_forthcomingFloatingNote->show();
    QPropertyAnimation* raiseAnimation = m_forthcomingFloatingNote->raiseNote();
    m_popupParallelGroup->addAnimation(raiseAnimation);
    // 如果已经有消息，那么前面的消息移出并隐藏；如果有消息正在执行动画，先等待
    if (m_shownFloatingNote)
    {
        QPropertyAnimation* hideAnimation = m_shownFloatingNote->dropNote();
        m_popupParallelGroup->addAnimation(hideAnimation);
        m_popupParallelGroup->disconnect();
        connect(m_popupParallelGroup, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::updatePointer);
    }
    // 如果没有消息，动画结束后将弹出标志复位，同时检查序列中有无后续事件（无需消息点操作）
    else 
    {
        //qDebug() << "[BLOCK] => checkPopupQueue";
        m_shownFloatingNote = m_forthcomingFloatingNote;
        m_forthcomingFloatingNote = nullptr;
        m_popupParallelGroup->disconnect();
        connect(m_popupParallelGroup, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::checkPopupQueue);
    }
    m_popupParallelGroup->start();
}

void FloatingNoteManager::adjustFloatingNote()
{
    // 意外情况发生时（例如在动画播放期间变化窗口），结束动画的位置并不符合预期，需要强制打断动画，重新计算结束位置，
    // 然后重新开始动画。一旦有任何调整窗口的行为，就将触发这个过程。
    QPoint floatingNoteHiddenPos = QPoint(m_hugou->width(), titleFrameHeight);
    QPoint floatingNoteShownPos = QPoint(m_hugou->width() - floatingNoteWidth - 20, titleFrameHeight);
    if (m_shownFloatingNote)
    {
        m_shownFloatingNote->setShownPos(floatingNoteShownPos);
        m_shownFloatingNote->setHiddenPos(floatingNoteHiddenPos);
    }
    if (m_forthcomingFloatingNote)
    {
        m_forthcomingFloatingNote->setShownPos(floatingNoteShownPos);
        m_forthcomingFloatingNote->setHiddenPos(floatingNoteHiddenPos);
    }
    if (!m_popupQueue.empty())
    {
        for (FloatingNote* floatingNote : m_popupQueue)
        {
            floatingNote->setShownPos(floatingNoteShownPos);
            floatingNote->setHiddenPos(floatingNoteHiddenPos);
            floatingNote->move(floatingNoteHiddenPos);
        }
    }
    if (m_dealLaterAnimation->state() == QPropertyAnimation::Running)
    {
        //qDebug() << "Status1";
        m_dealLaterAnimation->stop();
        dealLater();
    }
    if (m_dealNowAnimation->state() == QPropertyAnimation::Running)
    {
        //qDebug() << "Status2";
        m_dealNowAnimation->stop();
        dealNow();
    }
    if (m_popupParallelGroup->state() == QParallelAnimationGroup::Running)
    {
        //qDebug() << "Status3";
        m_popupParallelGroup->stop();
        m_forthcomingFloatingNote = m_backupForthcomingFloatingNote;
        m_shownFloatingNote = m_backupShownFloatingNote;
        //qDebug() << "[POP] From Status3";
        popupFloatingNote();
    }
    // 存在一种特殊情况。当大量消息涌入时，在消息更替的间隙，所有动画也是停滞状态。因此，当
    // 没有动画启动并且popupQueue.empty()时，才是真正的停止。
    if (m_dealLaterAnimation->state() == QPropertyAnimation::Stopped
        && m_dealNowAnimation->state() == QPropertyAnimation::Stopped
        && m_popupParallelGroup->state() == QParallelAnimationGroup::Stopped
        && m_popupQueue.empty())
    {
        //qDebug() << "Status4";
        m_forthcomingFloatingNote = m_backupForthcomingFloatingNote;
        m_shownFloatingNote = nullptr;
        m_popupFlag = false;
        //qDebug() << "[POP] From Status4";
        popupFloatingNote();
    }
}

// 槽函数
void FloatingNoteManager::updatePointer()
{
    // 隐藏已经完成动画的（原来正在展示的）浮动消息，并向隐藏列表末尾添加这个浮动消息。
    // 然后将已经完成动画的（原来即将展示的）浮动消息用指针shownFloatingNote指向。
    // 接着重置指针forthcomingFloatingNote。
    m_isAnimating = false;
    m_shownFloatingNote->hide();
    m_hiddenFloatingNoteList.push_back(m_shownFloatingNote);
    m_shownFloatingNote = m_forthcomingFloatingNote;
    m_forthcomingFloatingNote = nullptr;
    checkPopupQueue();
}

void FloatingNoteManager::deleteShownFloatingNote()
{
    m_isAnimating = false;
    m_shownFloatingNote->hide();
    m_shownFloatingNote->setParent(nullptr);
    delete m_shownFloatingNote;
    m_shownFloatingNote = m_forthcomingFloatingNote;
    m_forthcomingFloatingNote = nullptr;
    checkPopupQueue();
}

void FloatingNoteManager::checkPopupQueue()
{
    m_isAnimating = false;
    if (!m_popupQueue.empty())
    {
        m_popupFlag = false;
        m_forthcomingFloatingNote = m_popupQueue.dequeue();
        //qDebug() << "[POP] From popupQueue";
        popupFloatingNote();
    }
    else
    {
        m_popupFlag = true;
        if (m_shownFloatingNote)
        {
            m_shownFloatingNote->setEnabled(true);
            connect(m_shownFloatingNote, &FloatingNote::SignalDealLater, this, &FloatingNoteManager::dealLater);
            connect(m_shownFloatingNote, &FloatingNote::SignalDealNow, this, &FloatingNoteManager::dealNow);
        }
    }
}

void FloatingNoteManager::dealLater()
{
    m_isAnimating = true;
    m_dealLaterAnimation = m_shownFloatingNote->dropNote();
    connect(m_dealLaterAnimation, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::updatePointer);
    m_dealLaterAnimation->start();
}

void FloatingNoteManager::dealNow()
{
    m_isAnimating = true;
    m_dealNowAnimation = m_shownFloatingNote->dropNote();
    connect(m_dealNowAnimation, &QParallelAnimationGroup::finished, this, &FloatingNoteManager::deleteShownFloatingNote);
    m_dealNowAnimation->start();
}