#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QFile>
#include "Const.h"
#include "ButtonHoverWatcher.h"

QT_BEGIN_NAMESPACE

class Ui_FloatingNote
{
public:
	QString content = "";
	QFrame* floatingNoteFrame;
	QFrame* signZone;
	QLabel* contentZone;
	QFrame* buttonZone;
	QVBoxLayout* floatingNoteLayout;
	QVBoxLayout* frameLayout;
	QHBoxLayout* signLayout;
	QPushButton* sign;
	QLabel* timekeepingLabel;
	QHBoxLayout* buttonLayout;
	QPushButton* yesButton;
	QPushButton* noButton;
	QPushButton* dealLaterButton;
	ButtonHoverWatcher* yesButtonHoverWatcher;
	ButtonHoverWatcher* noButtonHoverWatcher;
	ButtonHoverWatcher* dealLaterButtonHoverWatcher;
	QPoint hiddenPos;
	QPoint shownPos;
	QPushButton* floatingNoteManagerButton;
	QPushButton* floatingNoteIcon;
	QHBoxLayout* queueLayout;
	QLabel* floatingNoteQueue;
	QLabel* firstNotePoint;
	QLabel* secondNotePoint;
	QLabel* thirdNotePoint;
	QLabel* forthNotePoint;
	QLabel* fifthNotePoint;
	std::vector<QLabel*> notePointQueue;
	QPixmap float_r = QPixmap("res/ico/float_r.png").scaled(QSize(10, 10));
	QPixmap float_b = QPixmap("res/ico/float_b.png").scaled(QSize(10, 10));
	QPixmap float_p = QPixmap("res/ico/float_p.png").scaled(QSize(10, 10));
	QPixmap float_o = QPixmap("res/ico/float_o.png").scaled(QSize(10, 10));
	QPixmap float_g = QPixmap("res/ico/float_g.png").scaled(QSize(10, 10));
	QPixmap float_w = QPixmap("res/ico/float_w.png").scaled(QSize(10, 10));
	QLabel* notePanel;

	void setupUi(QWidget* FloatingNote) 
	{
		// 主体
		FloatingNote->setFixedWidth(floatingNoteWidth);
		floatingNoteFrame = new QFrame(FloatingNote);
		floatingNoteFrame->setObjectName("floatingNoteFrame");
		floatingNoteLayout = new QVBoxLayout(FloatingNote);
		floatingNoteLayout->setObjectName("contentZone");
		frameLayout = new QVBoxLayout(floatingNoteFrame);
		frameLayout->setObjectName("frameLayout");
		frameLayout->setContentsMargins(5, 5, 5, 5);
		frameLayout->setSpacing(10);

		// 标志域
		signZone = new QFrame(FloatingNote);
		signZone->setObjectName("signZone");
		signLayout = new QHBoxLayout(signZone);
		signLayout->setObjectName("signLayout");
		signLayout->setSpacing(10);
		signLayout->setContentsMargins(0, 0, 0, 0);
		// 标志图标与文字
		sign = new QPushButton(FloatingNote);
		sign->setObjectName("sign");
		sign->setLayoutDirection(Qt::LeftToRight);
		sign->setFont(title2);
		sign->setIconSize(QSize(25, 25));
		// 时长标签
		timekeepingLabel = new QLabel("Now", FloatingNote);
		timekeepingLabel->setObjectName("timekeepingLabel");
		timekeepingLabel->setFont(timekeepingLabelFont);
		signLayout->addWidget(sign);
		signLayout->addWidget(timekeepingLabel, Qt::AlignLeft | Qt::AlignVCenter);
		signLayout->addStretch();

		// 内容域
		contentZone = new QLabel(FloatingNote);
		contentZone->setObjectName("contentZone");
		contentZone->setFont(contentFont);
		contentZone->setWordWrap(true);

		// 按钮域
		buttonZone = new QFrame(FloatingNote);
		buttonZone->setObjectName("buttonZone");
		buttonZone->setFixedHeight(40);
		buttonLayout = new QHBoxLayout(buttonZone);
		buttonLayout->setObjectName("buttonLayout");
		buttonLayout->setSpacing(0);
		buttonLayout->setContentsMargins(0, 0, 0, 0);
		// 确认按钮
		yesButton = new QPushButton(FloatingNote);
		yesButton->setObjectName("yesButton");
		yesButton->setIcon(QIcon("res/ico/yes_b.png"));
		yesButton->setFixedSize(floatingNoteButtonWidth, floatingNoteButtonHeight);
		yesButton->setText("Yes");
		yesButton->setFont(buttonFont);
		yesButtonHoverWatcher = new ButtonHoverWatcher("res/ico/yes_b.png", "res/ico/yes_w.png", FloatingNote);
		yesButton->installEventFilter(yesButtonHoverWatcher);
		// 取消按钮
		noButton = new QPushButton(FloatingNote);
		noButton->setObjectName("noButton");
		noButton->setIcon(QIcon("res/ico/close_bla.png"));
		noButton->setFixedSize(floatingNoteButtonWidth, floatingNoteButtonHeight);
		noButton->setText("No");
		noButton->setFont(buttonFont);
		noButtonHoverWatcher = new ButtonHoverWatcher("res/ico/close_bla.png", "res/ico/close_w.png", FloatingNote);
		noButton->installEventFilter(noButtonHoverWatcher);
		// 稍后处理按钮
		dealLaterButton = new QPushButton(FloatingNote);
		dealLaterButton->setObjectName("dealLaterButton");
		dealLaterButton->setIcon(QIcon("res/ico/dealLater_b.png"));
		dealLaterButton->setFixedSize(floatingNoteButtonWidth, floatingNoteButtonHeight);
		dealLaterButton->setText("Deal with later");
		dealLaterButton->setFont(buttonFont);
		dealLaterButtonHoverWatcher = new ButtonHoverWatcher("res/ico/dealLater_b.png", "res/ico/dealLater_w.png", FloatingNote);
		dealLaterButton->installEventFilter(dealLaterButtonHoverWatcher);
		buttonLayout->addWidget(yesButton);
		buttonLayout->addWidget(noButton);
		buttonLayout->addWidget(dealLaterButton);
		// 框架布局
		frameLayout->addWidget(signZone);
		frameLayout->addWidget(contentZone, Qt::AlignTop | Qt::AlignLeft);
		frameLayout->addWidget(buttonZone);
		// 整体布局
		floatingNoteLayout->setSpacing(0);
		floatingNoteLayout->addWidget(floatingNoteFrame);
		// 样式表设置
		QFile styleFile("res/theme/Global/floatingNote.qss");
		styleFile.open(QIODeviceBase::ReadOnly);
		FloatingNote->setStyleSheet(styleFile.readAll());
		styleFile.close();
	}
};

QT_END_NAMESPACE