#include "TitleBar.h"
#include "Var.h"

extern FloatingNoteManager floatingNoteManager;

TitleBar::TitleBar(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    // 父子关系（由子至父）：TitleBar->titleBarAndStackedWidget->HugouClass
    this->mainWindow = parent->parentWidget();

    //screenWidth = QApplication::primaryScreen()->availableGeometry().size().width();
    //screenHeight = QApplication::primaryScreen()->availableGeometry().size().height();
    //QRect generalGeometry = QRect((screenWidth - mainWindowWidth) / 2, (screenHeight - mainWindowHeight) / 2, mainWindowWidth, mainWindowHeight);
    //QRect maximumGeometry = QRect(0, 0, screenWidth, screenHeight);
    //engine.rootContext()->setContextProperty("mainWindow", mainWindow);
    //engine.rootContext()->setContextProperty("generalGeometry", generalGeometry);
    //engine.rootContext()->setContextProperty("maximumGeometry", maximumGeometry);
    //engine.load(QUrl("res/qml/scaledAnimation.qml"));

    floatingNotePanel = new FloatingNotePanel(mainWindow);

	connect(ui.floatingNotePanelButton, &QPushButton::clicked, floatingNotePanel, &FloatingNotePanel::showPanel);
	connect(ui.minimizeButton, &QPushButton::clicked, mainWindow, &QWidget::showMinimized);
    connect(ui.scaledButton, &QPushButton::clicked, this, &TitleBar::scale);
	connect(ui.closeButton, &QPushButton::clicked, mainWindow, &QWidget::close);
    connect(&floatingNoteManager, &FloatingNoteManager::SignalAnimationFinishedToTitleBar, this, &TitleBar::slideFloatingNotePoint);
    connect(floatingNotePanel, &FloatingNotePanel::blurBackground, this, [&]() {emit SignalBlurStackedWidget(); });
    connect(floatingNotePanel, &FloatingNotePanel::clearBackground, this, [&]() {emit SignalClearStackedWidget(); });
}

// 槽函数
void TitleBar::scale()
{
    if (mainWindow->isMaximized())
    {
        mainWindow->showNormal();
    }
    else
    {
        mainWindow->showMaximized();
    }
}

//void TitleBar::scale()
//{
//    if (isMaximum)
//    {
//        emit SignalRestore();
//        QMetaObject::invokeMethod(engine.rootObjects().value(0), "startRestoreAnimation");
//        ui.scaledButton->setIcon(QIcon("res/ico/maximum_w.png"));
//        isMaximum = false;
//    }
//    else
//    {
//        emit SignalMaximize();
//        QMetaObject::invokeMethod(engine.rootObjects().value(0), "startMaximumAnimation");
//        ui.scaledButton->setIcon(QIcon("res/ico/restore_w.png"));
//        isMaximum = true;
//    }
//    ui.scaledButton->setIconSize(titleButtonIconSize);
//}

void TitleBar::slideFloatingNotePoint()
{
    QParallelAnimationGroup* parallelGroup = new QParallelAnimationGroup;
    for (int i = 0; i < 5; i++)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(ui.notePointQueue[i], "pos", ui.floatingNoteQueue);
        animation->setDuration(100);
        animation->setStartValue(QPoint(5 + 10 * i, 0));
        animation->setEndValue(QPoint(5 + 10 * (i + 1), 0));
        parallelGroup->addAnimation(animation);
    }
    connect(parallelGroup, &QParallelAnimationGroup::finished, this, &TitleBar::floatFloatingNotePoint);
    parallelGroup->start(QParallelAnimationGroup::DeleteWhenStopped);
}

void TitleBar::floatFloatingNotePoint()
{
    QPropertyAnimation* animation0 = new QPropertyAnimation(ui.notePointQueue[4], "pos", ui.floatingNoteQueue);
    // 设置消息点必须在移动动画之后
    ui.notePointQueue[4]->setPixmap(ui.typePixmap[floatingNoteManager.getLatestHiddenFloatingNote()->type]);
    animation0->setDuration(100);
    animation0->setStartValue(QPoint(5, 15));
    animation0->setEndValue(QPoint(5, 0));
    connect(animation0, &QPropertyAnimation::finished, this, &TitleBar::allocateFloatingNotePoint);
    animation0->start(QAbstractAnimation::DeleteWhenStopped);
}

void TitleBar::allocateFloatingNotePoint()
{
    // 重新分配控件位置
    ui.notePointQueue.insert(ui.notePointQueue.begin(), ui.notePointQueue.back());
    ui.notePointQueue.pop_back();
    for (int i = 0; i < 5; ++i) ui.queueLayout->removeWidget(ui.notePointQueue[i]);
    for (int i = 0; i < 5; ++i) ui.queueLayout->addWidget(ui.notePointQueue[i]);
    floatingNoteManager.checkPopupQueue();
}

bool TitleBar::isOnMaxButton(QPoint windowPos)
{
    return QRect(ui.scaledButton->mapTo(mainWindow, QPoint(0, 0)), ui.scaledButton->size()).contains(windowPos);
}

bool TitleBar::isOnDragZone(QPoint windowPos)
{
    return QRect(ui.dragZone->mapTo(mainWindow, QPoint(0, 0)), ui.dragZone->size()).contains(windowPos);
}