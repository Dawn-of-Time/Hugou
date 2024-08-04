#include "IconTextButton.h"

IconTextButton::IconTextButton(QPixmap icon, QString text, QFont font, QWidget* parent) :
	QPushButton(parent)
{
	buttonLayout = new QHBoxLayout(this);
	iconZone = new QLabel(this);
	iconZone->setObjectName(text + "Icon");
	textZone = new QLabel(this);
	iconZone->setObjectName(text + "Text");
	// ��͸�ӿؼ���ʹ��괥���¼��Ķ����Ǹ��ؼ�
	iconZone->setAttribute(Qt::WA_TransparentForMouseEvents);
	textZone->setAttribute(Qt::WA_TransparentForMouseEvents);

	buttonLayout->setContentsMargins(10, 0, 10, 0);
	buttonLayout->setSpacing(12);

	icon = icon.scaled(QSize(18, 18), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	iconZone->setPixmap(icon);
	textZone->setText(text);
	textZone->setFont(font);

	buttonLayout->addStretch(1);
	buttonLayout->addWidget(iconZone);
	buttonLayout->addWidget(textZone);
	buttonLayout->addStretch(1);
}

