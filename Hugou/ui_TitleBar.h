#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QFile>
#include "Const.h"
#include "FloatingNote.h"
#include "FloatingNotePanel.h"
#include "ButtonHoverWatcher.h"


QT_BEGIN_NAMESPACE

class Ui_TitleBar
{
public:
    QHBoxLayout* titleLayout;
    QLabel* dragZone;
    QLabel* floatingNotePanelLabel;
    QVBoxLayout* floatingNotePanelLabelLayout;
    QLabel* floatingNotePanelButtonBackground;
    QVBoxLayout* floatingNotePanelButtonBackgroundLayout;
    QPushButton* floatingNotePanelButton;
    QPushButton* floatingNotePanelIcon;
    QHBoxLayout* queueLayout;
    QLabel* floatingNoteQueue;
    QLabel* firstNotePoint;
    QLabel* secondNotePoint;
    QLabel* thirdNotePoint;
    QLabel* forthNotePoint;
    QLabel* fifthNotePoint;
    QPixmap float_r = QPixmap("res/ico/float_r.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap float_b = QPixmap("res/ico/float_b.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap float_p = QPixmap("res/ico/float_p.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap float_o = QPixmap("res/ico/float_o.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap float_g = QPixmap("res/ico/float_g.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPixmap float_w = QPixmap("res/ico/float_w.png").scaled(QSize(10, 10), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    std::map<FloatingNote::Type, QPixmap> typePixmap =
    {
        {FloatingNote::Type::Success, float_g},
        {FloatingNote::Type::Dialog, float_p},
        {FloatingNote::Type::Information, float_b},
        {FloatingNote::Type::Warning, float_o},
        {FloatingNote::Type::Error, float_r}
    };
    std::vector<QLabel*> notePointQueue;
    QPushButton* helpButton;
    QPushButton* minimizeButton;
    QPushButton* scaledButton;
    QPushButton* closeButton;
    ButtonHoverWatcher* floatingNotePanelButtonHoverWatcher;
    //ButtonHoverWatcher* closeButtonHoverWatcher;
    //ButtonHoverWatcher* scaledButtonHoverWatcher;

    void setupUi(QWidget* titleBar)
    {
        titleBar->setMinimumWidth(titleFrameWidth);
        titleBar->setFixedHeight(titleFrameHeight);
        titleLayout = new QHBoxLayout(titleBar);
        titleLayout->setContentsMargins(0, 0, 0, 0);
        titleLayout->setSpacing(0);

        // 拖拽区域
        dragZone = new QLabel(titleBar);
        dragZone->setObjectName("dragZone");
        dragZone->setFixedHeight(titleButtonHeight);

        // 消息中心
        floatingNotePanelLabel = new QLabel(titleBar);
        floatingNotePanelLabel->setFixedSize(titleButtonWidth, titleButtonHeight);
        floatingNotePanelButtonBackground = new QLabel(floatingNotePanelLabel);
        floatingNotePanelButtonBackground->setObjectName("floatingNotePanelButtonBackground");
        floatingNotePanelButtonBackground->setFixedSize(titleButtonWidth, titleButtonHeight);
        floatingNotePanelButtonBackgroundLayout = new QVBoxLayout(floatingNotePanelButtonBackground);
        floatingNotePanelButtonBackgroundLayout->setContentsMargins(0, 0, 0, 0);
        floatingNotePanelButtonBackgroundLayout->setSpacing(0);
        floatingNotePanelIcon = new QPushButton(floatingNotePanelButtonBackground);
        floatingNotePanelIcon->setObjectName("floatingNotePanelIcon");
        floatingNotePanelIcon->setFixedSize(60, 35);
        floatingNotePanelIcon->setIcon(QIcon("res/ico/floatingNoteManager_w.png"));
        floatingNotePanelIcon->setIconSize(titleButtonIconSize);
        floatingNoteQueue = new QLabel(floatingNotePanelButtonBackground);
        floatingNoteQueue->setObjectName("floatingNoteQueue");
        floatingNoteQueue->setFixedHeight(10);
        queueLayout = new QHBoxLayout(floatingNoteQueue);
        queueLayout->setContentsMargins(5, 0, 0, 0);
        queueLayout->setSpacing(0);
        firstNotePoint = new QLabel(floatingNoteQueue);
        firstNotePoint->setObjectName("firstNotePoint");
        secondNotePoint = new QLabel(floatingNoteQueue);
        secondNotePoint->setObjectName("secondNotePoint");
        thirdNotePoint = new QLabel(floatingNoteQueue);
        thirdNotePoint->setObjectName("thirdNotePoint");
        forthNotePoint = new QLabel(floatingNoteQueue);
        forthNotePoint->setObjectName("forthNotePoint");
        fifthNotePoint = new QLabel(floatingNoteQueue);
        fifthNotePoint->setObjectName("fifthNotePoint");
        notePointQueue = { firstNotePoint, secondNotePoint, thirdNotePoint, forthNotePoint, fifthNotePoint };
        for (int i = 0; i < 5; ++i)
        {
            notePointQueue[i]->setFixedSize(QSize(10, 10));
            queueLayout->addWidget(notePointQueue[i]);
        }
        floatingNotePanelButtonBackgroundLayout->addWidget(floatingNotePanelIcon);
        floatingNotePanelButtonBackgroundLayout->addWidget(floatingNoteQueue);
        floatingNotePanelButton = new QPushButton(floatingNotePanelLabel);
        floatingNotePanelButton->setObjectName("floatingNotePanelButton");
        floatingNotePanelButton->setFixedSize(titleButtonWidth, titleButtonHeight);
        floatingNotePanelButtonHoverWatcher = new ButtonHoverWatcher(floatingNotePanelButtonBackground, "transparent", "rgba(255,255,255,80)", titleBar);
        floatingNotePanelButton->installEventFilter(floatingNotePanelButtonHoverWatcher);
        floatingNotePanelButton->raise();
        floatingNotePanelButton->setCursor(QCursor(Qt::PointingHandCursor));

        // 帮助按钮
        helpButton = new QPushButton(titleBar); 
        helpButton->setObjectName("helpButton");
        helpButton->setIcon(QIcon("res/ico/help_w.png"));
        helpButton->setIconSize(titleButtonIconSize);
        helpButton->setFixedSize(titleButtonWidth, titleButtonHeight);
        helpButton->setCursor(QCursor(Qt::PointingHandCursor));

        // 最小化按钮
        minimizeButton = new QPushButton(titleBar);
        minimizeButton->setObjectName("minimizeButton");
        minimizeButton->setIcon(QIcon("res/ico/minimize_w.png"));
        minimizeButton->setIconSize(titleButtonIconSize);
        minimizeButton->setFixedSize(titleButtonWidth, titleButtonHeight);
        minimizeButton->setCursor(QCursor(Qt::PointingHandCursor));

        // 最大化/还原按钮
        scaledButton = new QPushButton(titleBar);
        scaledButton->setObjectName("scaledButton");
        scaledButton->setIcon(QIcon("res/ico/maximum_w.png"));
        scaledButton->setIconSize(titleButtonIconSize);
        scaledButton->setFixedSize(titleButtonWidth, titleButtonHeight);
        scaledButton->setCursor(QCursor(Qt::PointingHandCursor));
        /*scaledButtonHoverWatcher = new ButtonHoverWatcher(QString("res/ico/island_b.png"), QString("res/ico/island_w.png"), titleBar);
        scaledButton->installEventFilter(scaledButtonHoverWatcher);*/

        // 关闭按钮
        closeButton = new QPushButton(titleBar);
        closeButton->setObjectName("closeButton");
        closeButton->setIcon(QIcon("res/ico/close_w.png"));
        closeButton->setIconSize(titleButtonIconSize);
        closeButton->setFixedSize(titleButtonWidth, titleButtonHeight);
        closeButton->setCursor(QCursor(Qt::PointingHandCursor));
        /*closeButtonHoverWatcher = new ButtonHoverWatcher(QString("res/ico/close_bla.png"), QString("res/ico/close_w.png"), titleBar);
        closeButton->installEventFilter(closeButtonHoverWatcher);*/

        titleLayout->addWidget(dragZone);
        titleLayout->addWidget(floatingNotePanelLabel);
        titleLayout->addWidget(helpButton);
        titleLayout->addWidget(minimizeButton);
        titleLayout->addWidget(scaledButton);
        titleLayout->addWidget(closeButton);

        // 样式表设置
        QFile styleFile("res/style/Default/titleBar.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        titleBar->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
};

QT_END_NAMESPACE