#include "Widgets/Include/Menu/Menu.h"

Menu::Menu(QWidget* parent)
	:QWidget(parent)
{
	setWindowFlags(Qt::Window);
	setAttribute(Qt::WA_TranslucentBackground);
	setupUi();
	connect(m_saveButton, &QPushButton::clicked, this, &Menu::save);
}

Menu::~Menu()
{
	//delete m_closeButtonHoverWatcher;
}

void Menu::setupUi()
{
	QFont saveButtonFont = QFont("NeverMind", 10, QFont::DemiBold);

	this->setFixedWidth(270);
	this->setObjectName("menu");
	this->setStyleSheet("QWidget #menu {background-color: white; border-radius: 5px; border: 1px solid #ACB1C6}");

	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(5, 5, 5, 5);
	m_layout->setSpacing(0);

	m_titleBar = new QWidget(this);
	m_titleBar->setFixedHeight(42);
	m_titleBar->setObjectName("menuTitleBar");
	m_titleBar->setStyleSheet("QWidget #menuTitleBar {background-color: transparent}");
	QHBoxLayout* titleBarLayout = new QHBoxLayout(m_titleBar);
	titleBarLayout->setContentsMargins(5, 0, 0, 0);
	titleBarLayout->setSpacing(0);
	titleBarLayout->setAlignment(Qt::AlignVCenter);

	m_icon = new QLabel(m_titleBar);
	m_icon->setFixedSize(16, 16);
	m_icon->setStyleSheet("border-radius: 8px; background-color: #468DFA");

	m_dragZone = new QWidget(this);
	m_dragZone->setObjectName("dragZone");
	m_dragZone->setFixedHeight(42);
	m_dragZone->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_saveButton = new QPushButton("Save", this);
	m_saveButton->setFont(saveButtonFont);
	m_saveButton->setObjectName("saveButton");
	m_saveButton->setFixedSize(48, 24);
	m_saveButton->setStyleSheet(
		"QPushButton {"
		"color: white;"
		"border: none;"
		"border-radius: 12px;"
		"background-color: #468DFA;"
		"}"
	);
	//m_closeButtonHoverWatcher = new ButtonHoverWatcher(QString(":/icon/close_black.ico"), QString(":/icon/close_white.ico"), this);
	//m_closeButton->installEventFilter(m_closeButtonHoverWatcher);

	titleBarLayout->addWidget(m_icon);
	titleBarLayout->addWidget(m_dragZone);
	titleBarLayout->addWidget(m_saveButton, Qt::AlignRight);

	m_centralWidget = new QWidget(this);
	m_centralWidgetLayout = new QVBoxLayout(m_centralWidget);
	m_centralWidgetLayout->setContentsMargins(5, 0, 5, 0);
	m_centralWidgetLayout->setSpacing(5);

	m_layout->addWidget(m_titleBar);
	m_layout->addWidget(m_centralWidget);
}

void Menu::addMenuItem(MenuItem* item) 
{ 
	if (m_centralWidgetLayout->count() != 0)
	{
		QWidget* spacer = new QWidget(m_centralWidget);
		spacer->setFixedHeight(2);
		spacer->setStyleSheet("background-color: #ACB1C6");
		m_centralWidgetLayout->addWidget(spacer);
	}
	m_centralWidgetLayout->addWidget(item);
}

void Menu::save()
{
	QMap<QString, QString> resultMap = {};
	for (QObject* item : m_centralWidget->children())
		if (item->inherits("MenuItem"))
		{
			QString key = qobject_cast<MenuItem*>(item)->name();
			QString value = qobject_cast<MenuItem*>(item)->save();
			resultMap.insert(key, value);
		}	 
	emit SignalSaved(resultMap);
	close();
}

bool Menu::event(QEvent* event)
{
	if (event->type() == QEvent::ActivationChange)
		if (QApplication::activeWindow() != this)
			this->close();
	return QWidget::event(event);
}

bool Menu::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)
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
		if (QRect(m_dragZone->mapTo(this, QPoint(0, 0)), m_dragZone->size()).contains(windowPos)) *result = HTCAPTION;
		if (*result != HTCLIENT) return true;
		return false;
	}
	}
	return QWidget::nativeEvent(eventType, message, result);
}

void Menu::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}