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
	QVBoxLayout* floatingNoteFrameLayout;
	QHBoxLayout* signLayout;
	QLabel* signIcon;
	QLabel* signTitle;
	QLabel* timekeepingLabel;
	QHBoxLayout* buttonLayout;
	QPushButton* yesButton;
	QPushButton* noButton;
	QPushButton* dealLaterButton;
	QPoint hiddenPos;
	QPoint shownPos;

	void setupUi(QWidget* floatingNote)
	{
		// 主体
		floatingNote->setFixedWidth(floatingNoteWidth);
		floatingNote->setObjectName("floatingNote");
		floatingNoteLayout = new QVBoxLayout(floatingNote);
		floatingNoteLayout->setContentsMargins(0, 0, 0, 0);
		floatingNoteLayout->setSpacing(0);

		floatingNoteFrame = new QFrame(floatingNote);
		floatingNoteFrame->setObjectName("floatingNoteFrame");
		floatingNoteFrame->setFixedWidth(floatingNoteWidth);
		floatingNoteFrameLayout = new QVBoxLayout(floatingNoteFrame);
		floatingNoteFrameLayout->setObjectName("floatingNoteFrameLayout");
		floatingNoteFrameLayout->setContentsMargins(10, 10, 10, 10);
		floatingNoteFrameLayout->setSpacing(10);

		// 标志域
		signZone = new QWidget(floatingNoteFrame);
		signZone->setObjectName("signZone");
		signLayout = new QHBoxLayout(signZone);
		signLayout->setObjectName("signLayout");
		signLayout->setSpacing(10);
		signLayout->setContentsMargins(0, 0, 0, 0);
		// 标志图标与文字
		signIcon = new QLabel(signZone);
		signIcon->setObjectName("signIcon");
		signIcon->setFixedSize(QSize(25, 25));
		signTitle = new QLabel(signZone);
		signTitle->setObjectName("signTitle");
		signTitle->setFont(signFont);
		// 时长标签
		timekeepingLabel = new QLabel("Now", signZone);
		timekeepingLabel->setObjectName("timekeepingLabel");
		timekeepingLabel->setFont(timekeepingLabelFont);
		signLayout->addWidget(signIcon);
		signLayout->addWidget(signTitle);
		signLayout->addWidget(timekeepingLabel);
		signLayout->addStretch();

		// 内容域
		contentZone = new QLabel(floatingNoteFrame);
		contentZone->setObjectName("contentZone");
		contentZone->setFont(contentFont);
		contentZone->setWordWrap(true);
		contentZone->setAlignment(Qt::AlignTop | Qt::AlignLeft);

		subcontentZone = new QLabel(floatingNoteFrame);
		subcontentZone->setObjectName("subcontentZone");
		subcontentZone->setFont(contentFont);
		subcontentZone->setWordWrap(true);
		subcontentZone->setHidden(true);
		subcontentZone->setAlignment(Qt::AlignTop | Qt::AlignLeft);

		// 按钮域
		buttonZone = new QWidget(floatingNoteFrame);
		buttonZone->setObjectName("buttonZone");
		buttonZone->setFixedHeight(40);
		buttonLayout = new QHBoxLayout(buttonZone);
		buttonLayout->setObjectName("buttonLayout");
		buttonLayout->setSpacing(10);
		buttonLayout->setContentsMargins(5, 5, 5, 5);
		// 确认按钮
		yesButton = new QPushButton("Checked!", buttonZone);
		yesButton->setObjectName("yesButton");
		yesButton->setFont(floatingNoteButtonFont);
		yesButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		yesButton->setCursor(QCursor(Qt::PointingHandCursor));
		// 取消按钮
		noButton = new QPushButton("No", buttonZone);
		noButton->setObjectName("noButton");
		noButton->setFont(floatingNoteButtonFont);
		noButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		noButton->setCursor(QCursor(Qt::PointingHandCursor));
		// 稍后处理按钮
		dealLaterButton = new QPushButton("Defer", buttonZone);
		dealLaterButton->setObjectName("dealLaterButton");
		dealLaterButton->setFont(floatingNoteButtonFont);
		dealLaterButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		dealLaterButton->setCursor(QCursor(Qt::PointingHandCursor));
		buttonLayout->addStretch(1);
		buttonLayout->addWidget(yesButton, 10);
		buttonLayout->addWidget(noButton, 10);
		buttonLayout->addWidget(dealLaterButton, 10);
		buttonLayout->addStretch(1);
		// 框架布局
		floatingNoteFrameLayout->addWidget(signZone);
		floatingNoteFrameLayout->addWidget(contentZone);
		floatingNoteFrameLayout->addWidget(subcontentZone);
		floatingNoteFrameLayout->addWidget(buttonZone);

		floatingNoteLayout->addWidget(floatingNoteFrame);

		// 样式表设置
		QFile styleFile(":/theme/Global/floatingNote.qss");
		styleFile.open(QIODeviceBase::ReadOnly);
		floatingNote->setStyleSheet(styleFile.readAll());
		styleFile.close();
	}
};

QT_END_NAMESPACE