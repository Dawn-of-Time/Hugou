#include "Widgets/Include/MemoSettingItem/MemoSettingItem.h"

MemoSettingItem::MemoSettingItem(QWidget* parent)
	:QWidget(parent)
{
	setupUi();
}

void MemoSettingItem::setupUi()
{
	// 字体清单
	QFont titleFont = QFont("NeverMind", 14, QFont::Medium);

	setFixedWidth(304);
	m_itemLayout = new QVBoxLayout(this);
	m_itemLayout->setContentsMargins(0, 0, 0, 0);
	m_itemLayout->setSpacing(5);
	m_itemLayout->setAlignment(Qt::AlignLeft);

	m_titleWidget = new QWidget(this);
	m_titleWidget->setFixedHeight(25);
	m_titleLayout = new QHBoxLayout(m_titleWidget);
	m_titleLayout->setContentsMargins(0, 0, 0, 0);
	m_titleLayout->setSpacing(0);

	m_title = new QLabel(m_titleWidget);
	m_title->setFont(titleFont);
	m_title->setFixedHeight(25);

	m_titleLayout->addWidget(m_title);
	m_titleLayout->addStretch();

	m_content = new QWidget(this);
	m_content->setObjectName("memoSettingItemContent");
	m_content->setStyleSheet("QWidget #memoSettingItemContent{background-color: rgba(255, 255, 255, 0.5); border-radius: 10px}");

	m_itemLayout->addWidget(m_titleWidget);
	m_itemLayout->addWidget(m_content);
}

MemoDetailItem::MemoDetailItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoDetailItem::setupUi()
{
	// 字体清单
	QFont detailFont = QFont("NeverMind", 12, QFont::Normal);

	resize(304, 80);
	setMinimumHeight(80);

	m_title->setText("Detail");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_detail = new QTextEdit(m_content);
	m_detail->setAcceptRichText(false);
	m_detail->setUndoRedoEnabled(true);
	m_detail->setFont(detailFont);
	m_detail->setStyleSheet("background-color: transparent; border: none");

	m_contentLayout->addWidget(m_detail);
}

MemoSubMemoItem::MemoSubMemoItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoSubMemoItem::setupUi()
{
	// 字体清单
	QFont numberFont = QFont("NeverMind", 10, QFont::Medium);
	QFont contentFont = QFont("NeverMind", 12, QFont::Normal);

	resize(304, 60);
	setMinimumHeight(60);

	m_title->setText("SubMemo");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(10);

	m_addSubMemoWidget = new QWidget(m_content);
	m_addSubMemoWidget->setFixedHeight(20);
	m_addSubMemoWidgetLayout = new QHBoxLayout(m_addSubMemoWidget);
	m_addSubMemoWidgetLayout->setContentsMargins(0, 0, 0, 0);
	m_addSubMemoWidgetLayout->setSpacing(8);

	m_subMemoNumber = new QLabel(QString::number(m_count + 1), m_addSubMemoWidget);
	m_subMemoNumber->setFixedSize(18, 18);
	m_subMemoNumber->setFont(numberFont);
	m_subMemoNumber->setAlignment(Qt::AlignCenter);
	m_subMemoNumber->setStyleSheet("background-color: #AEE4FD; border-radius: 9px");
	m_subMemoContent = new QLineEdit(m_addSubMemoWidget);
	m_subMemoContent->setFixedHeight(20);
	m_subMemoContent->setPlaceholderText("Click to add subMemo.");
	m_subMemoContent->setFont(numberFont);
	m_subMemoContent->setStyleSheet("border: none; background-color: transparent");
	m_addSubMemoWidgetLayout->addWidget(m_subMemoNumber);
	m_addSubMemoWidgetLayout->addWidget(m_subMemoContent);
	m_contentLayout->addWidget(m_addSubMemoWidget);
}


MemoAwardItem::MemoAwardItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoAwardItem::setupUi()
{
	// 字体清单
	QFont addAwardContentFont = QFont("NeverMind", 10, QFont::Medium);
	QFont addAwardSubContentFont = QFont("NeverMind", 8, QFont::Normal);

	resize(304, 80);

	m_title->setText("Award");
	m_content->setObjectName("awardContent");
	m_content->setStyleSheet("QWidget #awardContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_addAwardContent = new QLabel(tr("How to motivate yourself?"), m_content);
	m_addAwardContent->setFixedHeight(20);
	m_addAwardContent->setFont(addAwardContentFont);
	m_addAwardContent->setStyleSheet("color: #4F5E71");

	m_addAwardSubContent = new QLabel(tr("Click to add awards from the award repo."), m_content);
	m_addAwardSubContent->setFixedHeight(20);
	m_addAwardSubContent->setFont(addAwardSubContentFont);
	m_addAwardSubContent->setStyleSheet("color: #ACB1C6");

	m_contentLayout->addWidget(m_addAwardContent);
	m_contentLayout->addWidget(m_addAwardSubContent);
}

MemoReferenceItem::MemoReferenceItem(QWidget* parent)
	:MemoSettingItem(parent)
{
	setupUi();
}

void MemoReferenceItem::setupUi()
{
	// 字体清单
	QFont addReferenceContentFont = QFont("NeverMind", 10, QFont::Medium);
	QFont addReferenceSubContentFont = QFont("NeverMind", 8, QFont::Normal);

	resize(304, 80);

	m_title->setText("Reference");
	m_content->setObjectName("referenceContent");
	m_content->setStyleSheet("QWidget #referenceContent {border-radius: 10px; background-color: rgba(255, 255, 255, 0.5)}");
	m_contentLayout = new QVBoxLayout(m_content);
	m_contentLayout->setContentsMargins(12, 5, 12, 5);
	m_contentLayout->setSpacing(0);

	m_addReferenceContent = new QLabel(tr("What references are needed?"), m_content);
	m_addReferenceContent->setFixedHeight(20);
	m_addReferenceContent->setFont(addReferenceContentFont);
	m_addReferenceContent->setStyleSheet("color: #4F5E71");

	m_addReferenceSubContent = new QLabel(tr("Click to add References from the Reference repo."), m_content);
	m_addReferenceSubContent->setFixedHeight(20);
	m_addReferenceSubContent->setFont(addReferenceSubContentFont);
	m_addReferenceSubContent->setStyleSheet("color: #ACB1C6");

	m_contentLayout->addWidget(m_addReferenceContent);
	m_contentLayout->addWidget(m_addReferenceSubContent);
}


void MemoSettingItem::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
