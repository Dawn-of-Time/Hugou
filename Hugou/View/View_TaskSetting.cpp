#include "View_TaskSetting.h"

TaskSettingView::TaskSettingView(QWidget* parent)
	:QWidget(parent)
{
    setupUi();
}

void TaskSettingView::setupUi()
{
    // ×ÖÌåÇåµ¥
    const QFont generalTitleFont = QFont("Roboto", 14, QFont::Medium);
    const QFont firstLevelTitleFont = QFont("Roboto", 12, QFont::Normal);
    const QFont secondLevellTitleFont = QFont("Hind Siliguri", 12, QFont::Thin);

    this->setFixedSize(300, this->parentWidget()->height());
    m_taskSettingLayout = new QVBoxLayout(this);
    m_taskSettingLayout->setContentsMargins(0, 0, 0, 0);
    m_general = new QWidget(this);
    m_general->setObjectName("general");
    m_taskSettingLayout->addWidget(m_general);
    m_generalLayout = new QVBoxLayout(m_general);
    m_generalLayout->setContentsMargins(0, 0, 0, 0);
    m_generalLayout->setSpacing(2);

    m_title = new QWidget(m_general);
    m_title->setObjectName("title");
    m_title->setFixedHeight(50);
    m_titleLayout = new QHBoxLayout(m_title);
    m_titleLayout->setContentsMargins(15, 5, 15, 0);
    m_titleLabel = new QLabel("Add A Task", m_title);
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setFont(generalTitleFont);
    m_closeButton = new QPushButton(m_title);
    m_closeButton->setObjectName("closeButton");
    m_closeButton->setFixedSize(24, 24);
    m_closeButton->setIcon(QIcon(":/icon/close.ico"));
    m_titleLayout->addWidget(m_titleLabel);
    m_titleLayout->addStretch();
    m_titleLayout->addWidget(m_closeButton);

    m_list = new QWidget(m_general);
    m_list->setObjectName("list");
    m_listLayout = new QVBoxLayout(m_list);
    m_listLayout->setContentsMargins(0, 0, 0, 10);
    m_listLayout->setSpacing(0);

    m_generalLayout->addWidget(m_title);
    m_generalLayout->addWidget(m_list);

    m_sketchWidget = new QWidget(m_list);
    m_sketchWidgetLayout = new QVBoxLayout(m_sketchWidget);
    m_sketchTitle = new QLabel("Sketch", m_sketchWidget);
    m_sketchTitle->setObjectName("sketchTitle");
    m_sketchTitle->setFont(firstLevelTitleFont);
    m_sketch = new QLineEdit(m_sketchWidget);
    m_sketch->setObjectName("sketch");
    m_sketch->setFixedHeight(30);
    m_sketchWidgetLayout->addWidget(m_sketchTitle);
    m_sketchWidgetLayout->addWidget(m_sketch);

    m_taskTypeWidget = new QWidget(m_list);
    m_taskTypeWidgetLayout = new QVBoxLayout(m_taskTypeWidget);
    m_taskTypeTitle = new QLabel("Type", m_taskTypeWidget);
    m_taskTypeTitle->setObjectName("taskTypeTitle");
    m_taskTypeTitle->setFont(firstLevelTitleFont);
    m_briefTaskTypeWidget = new QWidget(m_taskTypeWidget);
    m_briefTaskTypeWidgetLayout = new QHBoxLayout(m_briefTaskTypeWidget);
    m_briefTaskTypeWidget->hide();
    m_detailedTaskTypeWidget = new QWidget(m_taskTypeWidget);
    m_detailedTaskTypeWidget->setObjectName("detailedTaskTypeWidget");
    m_detailedTaskTypeWidgetLayout = new QVBoxLayout(m_detailedTaskTypeWidget);
    m_detailedTaskTypeWidgetLayout->setSpacing(2);
    //for (QMap<QString, QString>::const_iterator it = taskTypeMap.begin(); it != taskTypeMap.end(); ++it)
    //{
    //    QString type = it.key();
    //    FadeEffectButton* button = new FadeEffectButton(QPixmap(), QSize(16, 16), type, secondLevellTitleFont, m_detailedTaskTypeWidget);
    //    button->setObjectName(type + "TypeButton");
    //    button->setFixedHeight(20);
    //    button->setProperty("status", "default");
    //    button->setStyleSheet(QString(
    //        "FadeEffectButton[status=\"default\"] {"
    //        "border-radius: 10px;"
    //        "background-color: white;"
    //        "}"
    //        "FadeEffectButton[status=\"default\"] > QLabel {"
    //        "color: %1;"
    //        "background-color: transparent;"
    //        "}"
    //        "FadeEffectButton[status=\"current\"] {"
    //        "border-radius: 10px;"
    //        "background-color: %1;"
    //        "}"
    //        "FadeEffectButton[status=\"current\"] > QLabel {"
    //        "color: white;"
    //        "background-color: transparent;"
    //        "}"
    //    ).arg(taskTypeMap[type]));
    //    button->setBackgroundWidgetStyleSheet(QString(
    //        "border-radius: 10px; background-color: rgba(0, 0, 255, 0.1);"
    //    ));
    //    m_detailedTaskTypeWidgetLayout->addWidget(button);
    //}
    m_addTaskTypeButton = new FadeEffectButton(QPixmap(), QSize(16, 16), "Add Type", secondLevellTitleFont, m_detailedTaskTypeWidget);
    m_addTaskTypeButton->setFixedHeight(20);
    m_addTaskTypeButton->setBackgroundWidgetStyleSheet("border-radius: 10px; border: 1px solid #D6D6D6; ");
    m_detailedTaskTypeWidgetLayout->addWidget(m_addTaskTypeButton);
    m_taskTypeWidgetLayout->addWidget(m_taskTypeTitle);
    m_taskTypeWidgetLayout->addWidget(m_detailedTaskTypeWidget);

    m_timeWidget = new QWidget(m_list);
    m_timeWidgetLayout = new QVBoxLayout(m_timeWidget);
    m_timeTitle = new QLabel("Time", m_timeWidget);
    m_timeTitle->setFont(firstLevelTitleFont);
    m_timeTitle->setObjectName("timeTitle");
    m_time = new QWidget(m_timeWidget);
    m_taskTypeWidgetLayout->addWidget(m_timeTitle);
    m_taskTypeWidgetLayout->addWidget(m_time);

    m_showOrHideButton = new QPushButton("Show more");
    m_showOrHideButton->setObjectName("showOrHideButton");

    m_postponeWidget = new QWidget(m_list);
    m_postponeWidgetLayout = new QVBoxLayout(m_postponeWidget);

    m_importanceWidget = new QWidget(m_list);

    m_detailWidget = new QWidget(m_list);
    m_detailWidgetLayout = new QVBoxLayout(m_detailWidget);
    m_detailTitle = new QLabel("Detail", m_detailWidget);
    m_detailTitle->setFont(firstLevelTitleFont);
    m_detailTitle->setObjectName("detailTitle");
    m_detail = new QLineEdit(m_detailWidget);
    m_detail->setObjectName("detail");
    m_detail->setFixedHeight(30);
    m_detailWidgetLayout->addWidget(m_detailTitle);
    m_detailWidgetLayout->addWidget(m_detail);

    m_awardWidget = new QWidget(m_list);
    m_awardWidgetLayout = new QVBoxLayout(m_awardWidget);
    m_awardTitle = new QLabel("Award", m_awardWidget);
    m_awardTitle->setFont(firstLevelTitleFont);
    m_awardTitle->setObjectName("awardTitle");
    m_award = new QLineEdit(m_awardWidget);
    m_award->setObjectName("award");
    m_award->setFixedHeight(30);
    m_awardWidgetLayout->addWidget(m_awardTitle);
    m_awardWidgetLayout->addWidget(m_award);

    m_planPanel = new QWidget(m_list);

    m_commitButton = new QPushButton("Commit", m_list);

    m_listLayout->addWidget(m_sketchWidget);
    m_listLayout->addWidget(m_taskTypeWidget);
    m_listLayout->addWidget(m_timeWidget);
    m_listLayout->addWidget(m_showOrHideButton);
    m_listLayout->addWidget(m_postponeWidget);
    m_listLayout->addWidget(m_importanceWidget);
    m_listLayout->addWidget(m_detailWidget);
    m_listLayout->addWidget(m_awardWidget);
    m_listLayout->addWidget(m_planPanel);
    m_listLayout->addWidget(m_commitButton);


    QFile styleFile(":/theme/Global/taskSetting.qss");
    styleFile.open(QIODeviceBase::ReadOnly);
    this->setStyleSheet(styleFile.readAll());
    styleFile.close();
}

void TaskSettingView::slideIn()
{
    m_animationFlag = AnimationFlag::SlideIn;
    if (m_slideAnimation) delete m_slideAnimation;
    m_slideAnimation = new QPropertyAnimation(this, "pos");
    m_slideAnimation->setEndValue(QPoint(this->parentWidget()->width() - this->width(), 0));
    m_slideAnimation->setDuration(400);
    m_slideAnimation->setEasingCurve(QEasingCurve::OutCirc);
    m_slideAnimation->disconnect();
    connect(m_slideAnimation, &QPropertyAnimation::finished, [&]()
        {
            m_isShown = true;
        });
    m_slideAnimation->start();
}

void TaskSettingView::slideOut()
{
    m_animationFlag = AnimationFlag::SlideOut;
    m_isShown = false;
    if (m_slideAnimation) delete m_slideAnimation;
    m_slideAnimation = new QPropertyAnimation(this, "pos");
    m_slideAnimation->setEndValue(QPoint(this->parentWidget()->width(), 0));
    m_slideAnimation->setDuration(400);
    m_slideAnimation->setEasingCurve(QEasingCurve::OutCirc);
    m_slideAnimation->disconnect();
    connect(m_slideAnimation, &QPropertyAnimation::finished, [&]()
        {
            this->close();
            this->parentWidget()->layout()->removeWidget(this);
            this->setParent(nullptr);
            delete this;
        });
    m_slideAnimation->start();
}

void TaskSettingView::adjustView()
{
    if (m_slideAnimation && m_slideAnimation->state() == QPropertyAnimation::Running)
    {
        m_slideAnimation->stop();
        switch (m_animationFlag)
        {
        case TaskSettingView::SlideIn:
            this->setFixedSize(300, this->parentWidget()->height());
            this->move(QPoint(this->parentWidget()->width() - this->width(), 0));
            break;
        case TaskSettingView::SlideOut:
            this->move(QPoint(this->parentWidget()->width(), 0));
            break;
        default:
            break;
        }
    }
    if (m_isShown) 
    {
        this->setFixedSize(300, this->parentWidget()->height());
        this->move(QPoint(this->parentWidget()->width() - this->width(), 0));
    }
}