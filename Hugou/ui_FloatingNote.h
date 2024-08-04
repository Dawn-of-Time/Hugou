#pragma once

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include "Const.h"
#include "IconTextButtonHoverWatcher.h"
#include "IconTextButton.h"

QT_BEGIN_NAMESPACE

class Ui_FloatingNote
{
public:
	QFrame* floatingNoteFrame;
	QString content = "";
	QWidget* signZone;
	QLabel* contentZone;
	QLabel* subcontentZone;
	QWidget* buttonZone;
	QVBoxLayout* floatingNoteLayout;
	QHBoxLayout* signLayout;
	QLabel* signIcon;
	QLabel* signTitle;
	QLabel* timekeepingLabel;
	QHBoxLayout* buttonLayout;
	IconTextButton* yesButton;
	IconTextButton* noButton;
	IconTextButton* dealLaterButton;
	IconTextButtonHoverWatcher* yesButtonHoverWatcher;
	IconTextButtonHoverWatcher* noButtonHoverWatcher;
	IconTextButtonHoverWatcher* dealLaterButtonHoverWatcher;
	QPoint hiddenPos;
	QPoint shownPos;

	void setupUi(QWidget* floatingNote)
	{
		// 主体
		floatingNote->setFixedWidth(floatingNoteWidth);
		floatingNote->setObjectName("floatingNote");
		floatingNoteFrame = new QFrame(floatingNote);
		floatingNoteFrame->setObjectName("floatingNoteFrame");
		floatingNoteFrame->setFixedWidth(floatingNoteWidth);
		floatingNoteLayout = new QVBoxLayout(floatingNoteFrame);
		floatingNoteLayout->setObjectName("floatingNoteLayout");
		floatingNoteLayout->setContentsMargins(10, 10, 10, 10);
		floatingNoteLayout->setSpacing(10);

		// 标志域
		signZone = new QWidget(floatingNoteFrame);
		signZone->setObjectName("signZone");
		signLayout = new QHBoxLayout(signZone);
		signLayout->setObjectName("signLayout");
		signLayout->setSpacing(10);
		signLayout->setContentsMargins(0, 0, 0, 0);
		// 标志图标与文字
		signIcon = new QLabel(signZone);
		signIcon->setObjectName("sign");
		signIcon->setFixedSize(QSize(25, 25));
		signTitle = new QLabel(signZone);
		signTitle->setFont(signFont);
		// 时长标签
		timekeepingLabel = new QLabel("---Now", signZone);
		timekeepingLabel->setObjectName("timekeepingLabel");
		timekeepingLabel->setFont(timekeepingLabelFont);
		timekeepingLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
		signLayout->addWidget(signIcon, 0, Qt::AlignBottom);
		signLayout->addWidget(signTitle, 0, Qt::AlignBottom);
		signLayout->addWidget(timekeepingLabel, 0, Qt::AlignBottom);
		signLayout->addStretch();

		// 内容域
		contentZone = new QLabel(floatingNoteFrame);
		contentZone->setObjectName("contentZone");
		contentZone->setFont(contentFont);
		contentZone->setWordWrap(true);

		subcontentZone = new QLabel(floatingNoteFrame);
		subcontentZone->setObjectName("subcontentZone");
		subcontentZone->setFont(contentFont);
		subcontentZone->setWordWrap(true);
		subcontentZone->setHidden(true);

		// 按钮域
		buttonZone = new QWidget(floatingNoteFrame);
		buttonZone->setObjectName("buttonZone");
		buttonZone->setFixedHeight(40);
		buttonLayout = new QHBoxLayout(buttonZone);
		buttonLayout->setObjectName("buttonLayout");
		buttonLayout->setSpacing(10);
		buttonLayout->setContentsMargins(5, 5, 5, 5);
		// 确认按钮
		yesButton = new IconTextButton(QPixmap("res/ico/yes_g.png"), "Yes", floatingNoteButtonFont, buttonZone);
		yesButton->setObjectName("yesButton");
		yesButton->setFont(buttonFont);
		yesButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		yesButtonHoverWatcher = new IconTextButtonHoverWatcher("res/ico/yes_g.png", "res/ico/yes_w.png", floatingNoteButtonIconSize, floatingNote);
		yesButton->installEventFilter(yesButtonHoverWatcher);
		// 取消按钮
		noButton = new IconTextButton(QPixmap("res/ico/close_bla.png"), "No", floatingNoteButtonFont, buttonZone);
		noButton->setObjectName("noButton");
		noButton->setFont(buttonFont);
		noButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		noButtonHoverWatcher = new IconTextButtonHoverWatcher("res/ico/close_bla.png", "res/ico/close_w.png", floatingNoteButtonIconSize, floatingNote);
		noButton->installEventFilter(noButtonHoverWatcher);
		// 稍后处理按钮
		dealLaterButton = new IconTextButton(QPixmap("res/ico/dealLater_b.png"), "Handle later", floatingNoteButtonFont, buttonZone);
		dealLaterButton->setObjectName("dealLaterButton");
		dealLaterButton->setFont(buttonFont);
		dealLaterButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		dealLaterButtonHoverWatcher = new IconTextButtonHoverWatcher("res/ico/dealLater_b.png", "res/ico/dealLater_w.png", floatingNoteButtonIconSize, floatingNote);
		dealLaterButton->installEventFilter(dealLaterButtonHoverWatcher);
		buttonLayout->addStretch(1);
		buttonLayout->addWidget(yesButton, 10);
		buttonLayout->addWidget(noButton, 10);
		buttonLayout->addWidget(dealLaterButton, 10);
		buttonLayout->addStretch(1);
		// 框架布局
		floatingNoteLayout->addWidget(signZone);
		floatingNoteLayout->addWidget(contentZone, Qt::AlignTop | Qt::AlignLeft);
		floatingNoteLayout->addWidget(subcontentZone, Qt::AlignTop | Qt::AlignLeft);
		floatingNoteLayout->addWidget(buttonZone);

		// 样式表设置
		QFile styleFile("res/theme/Global/floatingNote.qss");
		styleFile.open(QIODeviceBase::ReadOnly);
		floatingNote->setStyleSheet(styleFile.readAll());
		styleFile.close();
	}
};

QT_END_NAMESPACE