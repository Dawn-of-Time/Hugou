#include "AsideBar.h"
#include "Var.h"

extern FloatingNoteManager floatingNoteManager;

AsideBar::AsideBar(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
    
	// �ź����
	connect(ui.workSpaceButton, &QPushButton::clicked, this, &AsideBar::switchOverStackedWidget);
    connect(ui.settingButton, &QPushButton::clicked, this, &AsideBar::switchOverStackedWidget);
}

// �ӿؼ�λ����Ui��������ܱ���ȷ��ȡ
void AsideBar::showEvent(QShowEvent* event)
{
    ui.workSpaceButtonHoverWatcher = new ButtonHoverWatcher(ui.workSpaceButton->pos(), QPoint(ui.workSpaceButton->pos().x() + 5, ui.workSpaceButton->pos().y()), ButtonHoverWatcher::Direction::Horizontal);
    ui.workSpaceButton->installEventFilter(ui.workSpaceButtonHoverWatcher);
    ui.settingButtonHoverWatcher = new ButtonHoverWatcher(ui.settingButton->pos(), QPoint(ui.settingButton->pos().x() + 5, ui.settingButton->pos().y()), ButtonHoverWatcher::Direction::Horizontal);
    ui.settingButton->installEventFilter(ui.settingButtonHoverWatcher);
}

void AsideBar::switchOverStackedWidget()
{
    QObject* sender = QObject::sender();
    if (sender) {
        if (sender->objectName() == "workSpaceButton") {
            ui.workSpaceButton->setEnabled(false);
            ui.settingButton->setEnabled(true);
            ui.workSpaceButton->setIcon(QPixmap("res/ico/workSpace_b.png"), QSize(18, 18));
            ui.settingButton->setIcon(QPixmap("res/ico/setting_w.png"), QSize(18, 18));
            ui.workSpaceButton->setProperty("status", "current");
            ui.settingButton->setProperty("status", "default");
            this->setStyleSheet(this->styleSheet());
            emit SignalChangeStackedWidget(0);
        }
        if (sender->objectName() == "settingButton") {
            ui.workSpaceButton->setEnabled(true);
            ui.settingButton->setEnabled(false);
            ui.workSpaceButton->setIcon(QPixmap("res/ico/workSpace_w.png"), QSize(18, 18));
            ui.settingButton->setIcon(QPixmap("res/ico/setting_b.png"), QSize(18, 18));
            ui.workSpaceButton->setProperty("status", "default");
            ui.settingButton->setProperty("status", "current");
            this->setStyleSheet(this->styleSheet());
            emit SignalChangeStackedWidget(1);
        }
    }
}