#include "IconTextButton.h"
#include "Var.h"

IconTextButton::IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent) :
	QPushButton(parent)
{
	buttonLayout = new QHBoxLayout(this);
	iconZone = new QLabel(this);
	iconZone->setObjectName(text + "Icon");
	iconZone->setFixedSize(16, 16);
	textZone = new QLabel(this);
	textZone->setObjectName(text + "Text");
	// 穿透子控件，使鼠标触发事件的对象是父控件
	iconZone->setAttribute(Qt::WA_TransparentForMouseEvents);
	textZone->setAttribute(Qt::WA_TransparentForMouseEvents);

	buttonLayout->setContentsMargins(10, 0, 10, 0);
	buttonLayout->setSpacing(12);

	icon.setDevicePixelRatio(getScale());
	iconZone->setPixmap(icon);
	textZone->setText(text);
	textZone->setFont(font);

	buttonLayout->addWidget(iconZone, Qt::AlignVCenter);
	buttonLayout->addWidget(textZone, Qt::AlignVCenter);
	buttonLayout->addStretch();
}

