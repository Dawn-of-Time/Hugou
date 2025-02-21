#include "PopupWidget.h"

PopupWidget::PopupWidget(QString title, QWidget* parent)
	:QWidget(parent), m_title(title)
{
	setupUi();
	setWindowModality(Qt::ApplicationModal);
	setAttribute(Qt::WA_DeleteOnClose);
	// 接入windows API。
	HWND hWnd = (HWND)winId();
	LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
	SetWindowLongPtr(
		hWnd,
		GWL_STYLE,
		style
		| WS_MINIMIZEBOX
		| WS_MAXIMIZEBOX
		| WS_CAPTION
		| CS_DBLCLKS
		| WS_THICKFRAME
	);

	connect(m_closeButton, &QPushButton::clicked, this, &PopupWidget::close);
}

PopupWidget::~PopupWidget()
{
	delete m_closeButtonHoverWatcher;
}

void PopupWidget::setupUi()
{
	// 字体清单
	QFont widgetNameFont = QFont("NeverMind", 16, QFont::Normal);

	this->setStyleSheet("background-color: white");

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	QLabel* widgetName = new QLabel(m_title, this);
	//widgetName->setFixedWidth(80);
	widgetName->setFont(widgetNameFont);
	widgetName->adjustSize();

	m_titleBar = new QWidget(this);
	QHBoxLayout* titleBarLayout = new QHBoxLayout(m_titleBar);
	titleBarLayout->setContentsMargins(16, 0, 0, 16);
	titleBarLayout->setSpacing(0);

	m_dragZone = new QWidget(this);
	m_dragZone->setObjectName("dragZone");
	m_dragZone->setFixedHeight(titleFrameHeight);
	m_dragZone->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_closeButton = new QPushButton(this);
	m_closeButton->setObjectName("closeButton");
	m_closeButton->setIcon(QIcon(":/icon/close_black.ico"));
	m_closeButton->setFixedSize(titleButtonWidth, titleButtonHeight);
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
		// 注：拦截WM_NCCALCSIZE消息，以防后续坐标计算错位。
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
		// 为了获取到正确的全局鼠标位置，应将GET_X_LPARAM和GET_Y_LPARAM得到的结果除以缩放倍数。
		QPoint globalPos = QPoint(GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)) / devicePixelRatio();
		QPoint windowPos = mapFromGlobal(globalPos);
		if (QRect(m_dragZone->mapTo(this, QPoint(0, 0)), m_dragZone->size()).contains(windowPos)) * result = HTCAPTION;
		if (*result != HTCLIENT) return true;
		return false;
	}
	}
	return QWidget::nativeEvent(eventType, message, result);
}