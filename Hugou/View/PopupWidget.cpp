#include "View/Include/PopupWidget.h"

PopupWidget::PopupWidget(const QString& title)
	:QWidget(globalHugou), m_title(title)
{
	setupUi();
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Window);
}

PopupWidget::~PopupWidget()
{
	delete m_closeButtonHoverWatcher;
}

void PopupWidget::setupUi()
{
	// ×ÖÌåÇåµ¥
	QFont widgetNameFont = QFont("NeverMind", 14, QFont::Normal);

	this->setObjectName("popupWidget");
	this->setStyleSheet("#popupWidget {background-color: white; border-radius: 5px}");

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	QLabel* widgetName = new QLabel(m_title, this);
	widgetName->setFont(widgetNameFont);
	widgetName->adjustSize();

	m_titleBar = new QWidget(this);
	QHBoxLayout* titleBarLayout = new QHBoxLayout(m_titleBar);
	titleBarLayout->setContentsMargins(16, 0, 0, 16);
	titleBarLayout->setSpacing(0);

	m_dragZone = new QWidget(this);
	m_dragZone->setObjectName("dragZone");
	m_dragZone->setFixedHeight(42);
	m_dragZone->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	
	m_closeButton = new QPushButton(this);
	m_closeButton->setObjectName("closeButton");
	m_closeButton->setIcon(QIcon(":/icon/close_black.ico"));
	m_closeButton->setIconSize(QSize(16, 16));
	m_closeButton->setFixedSize(56, 42);
	m_closeButton->setStyleSheet(
		"QPushButton {"
		"border: none;"
		"background-color: transparent;"
		"}"
		"QPushButton:hover {"
		"border: none;"
		"background-color: red;"
		"}");
	m_closeButtonHoverWatcher = new ButtonHoverWatcher(QString(":/icon/close_black.ico"), QString(":/icon/close_white.ico"), this);
	m_closeButton->installEventFilter(m_closeButtonHoverWatcher);

	titleBarLayout->addWidget(widgetName);
	titleBarLayout->addWidget(m_dragZone);
	titleBarLayout->addWidget(m_closeButton, Qt::AlignRight);

	m_layout->addWidget(m_titleBar);
}

void PopupWidget::setCentralWidget(QWidget* widget)
{
	m_layout->addWidget(widget);
}

bool PopupWidget::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
{
	MSG* msg = static_cast<MSG*>(message);
	switch (msg->message)
	{
	case WM_NCCALCSIZE:
	{
		*result = HTNOWHERE;
		return true;
	}
	case WM_ACTIVATE:
	{
		MARGINS margins = { 0, 1, 0, 1 };
		HRESULT hr = DwmExtendFrameIntoClientArea(msg->hwnd, &margins);
		*result = hr;
		return true;
	}
	case WM_NCHITTEST:
	{
		*result = HTCLIENT;
		QPoint globalPos = QCursor::pos();
		QPoint windowPos = mapFromGlobal(globalPos);
		if (QRect(m_dragZone->mapTo(this, QPoint(0, 0)), m_dragZone->size()).contains(windowPos)) * result = HTCAPTION;
		if (*result != HTCLIENT) return true;
		return false;
	}
	}
	return QWidget::nativeEvent(eventType, message, result);
}