#include "View_Preference.h"

PreferenceView::PreferenceView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
}

PreferenceView::~PreferenceView()
{
    for (PreferenceItem* item : m_preferenceItemList)
        delete item;
}

void PreferenceView::setupUi()
{
    this->setObjectName("preference");
    m_preferenceLayout = new QHBoxLayout(this);
    m_preferenceLayout->setSpacing(0);
    m_preferenceLayout->setContentsMargins(10, 10, 10, 10);

    // 左栏
    m_preferenceLeftWidget = new QWidget(this);
    m_preferenceLeftWidget->setObjectName("preferenceLeftWidget");
    m_preferenceLeftWidget->setFixedWidth(200);
    m_preferenceLeftLayout = new QVBoxLayout(m_preferenceLeftWidget);
    m_preferenceLeftLayout->setObjectName("preferenceLeftLayout");
    m_preferenceLeftLayout->setSpacing(0);
    m_preferenceLeftLayout->setContentsMargins(0, 0, 0, 0);

    // 搜索区域
    m_searchLineEdit = new QLineEdit(m_preferenceLeftWidget);
    m_searchLineEdit->setFixedHeight(30);
    m_searchLineEdit->setObjectName("searchLineEdit");
    m_searchLineEdit->setPlaceholderText(searchText);
    m_searchLineEdit->setFont(QFont("Hind Siliguri", 13));
    QPalette searchPalette = m_searchLineEdit->palette();
    searchPalette.setColor(searchPalette.PlaceholderText, QColor("#cccccc"));
    m_searchButton = new QPushButton(m_searchLineEdit);
    m_searchButton->setObjectName("searchButton");
    m_searchButton->setIcon(QIcon(":/icon/search_bla.ico"));
    m_searchButton->setCursor(Qt::ArrowCursor);
    QWidgetAction* searchAction = new QWidgetAction(m_searchLineEdit);
    searchAction->setDefaultWidget(m_searchButton);
    m_searchLineEdit->addAction(searchAction, QLineEdit::TrailingPosition);
    m_searchButtonHoverWatcher = new ButtonHoverWatcher(QString(":/icon/search_bla.ico"), QString(":/icon/search_blu.ico"), this);
    m_searchButton->installEventFilter(m_searchButtonHoverWatcher);

    // 目录
    m_preferenceTreeStackedWidget = new QStackedWidget(m_preferenceLeftWidget);
    m_preferenceTreeWidget = new QTreeWidget(m_preferenceTreeStackedWidget);
    m_preferenceTreeWidget->setHeaderHidden(true);
    formTree();
    m_preferenceTreeWidget->setFont(QFont("Hind Siliguri", 13));
    m_searchpreferenceNullLabel = new QLabel("No matches were found.", m_preferenceTreeStackedWidget);
    m_searchpreferenceNullLabel->setVisible(false); // 默认不显示“未找到匹配项”
    m_searchpreferenceNullLabel->setFont(QFont("Hind Siliguri", 13));
    m_searchpreferenceNullLabel->setAlignment(Qt::AlignTop);
    m_preferenceTreeStackedWidget->addWidget(m_preferenceTreeWidget);
    m_preferenceTreeStackedWidget->addWidget(m_searchpreferenceNullLabel);
    m_preferenceTreeStackedWidget->setCurrentIndex(0);

    m_preferenceLeftLayout->addWidget(m_searchLineEdit);
    m_preferenceLeftLayout->addWidget(m_preferenceTreeStackedWidget);

    // 右栏
    m_preferenceRightWidget = new QWidget(this);
    m_preferenceRightWidget->setObjectName("preferenceRightWidget");
    m_preferenceRightLayout = new QVBoxLayout(m_preferenceRightWidget);
    m_preferenceRightLayout->setObjectName("preferenceRightLayout");
    m_preferenceRightLayout->setSpacing(0);
    m_preferenceRightLayout->setContentsMargins(10, 0, 0, 0);

    m_preferenceContentListWidget = new QListWidget(m_preferenceRightWidget);
    formContentList();
    m_preferenceContentListWidget->setSelectionRectVisible(false);
    m_preferenceRightLayout->addWidget(m_preferenceContentListWidget);

    m_preferenceLayout->addWidget(m_preferenceLeftWidget);
    m_preferenceLayout->addWidget(m_preferenceRightWidget);
}

void PreferenceView::formTree()
{
    // 一级目录
    QTreeWidgetItem* item1 = new QTreeWidgetItem(m_preferenceTreeWidget);
    item1->setText(0, "Common");
    item1->setIcon(0, QIcon(":/icon/common.ico"));
    m_preferenceTreeWidget->addTopLevelItem(item1);
    QTreeWidgetItem* item2 = new QTreeWidgetItem(m_preferenceTreeWidget);
    item2->setText(0, "Task");
    item2->setIcon(0, QIcon(":/icon/export.ico"));
    m_preferenceTreeWidget->addTopLevelItem(item2);

    // 二级目录
    QTreeWidgetItem* item1_1 = new QTreeWidgetItem(item1);
    item1_1->setText(0, "Appearance");
    item1_1->setIcon(0, QIcon(":/icon/appearance.ico"));
    QTreeWidgetItem* item1_2 = new QTreeWidgetItem(item1);
    item1_2->setText(0, "Country/Region");
    item1_2->setIcon(0, QIcon(":/icon/country_region.ico"));
    QTreeWidgetItem* item2_1 = new QTreeWidgetItem(item2);
    item2_1->setText(0, "Recycle Bin");
    item2_1->setIcon(0, QIcon(":/icon/country_region.ico"));
}

void PreferenceView::formContentList()
{
    // 
    //QListWidgetItem* headSpaceItem = new QListWidgetItem(m_preferenceContentListWidget);
    //QLabel* headSpace = new QLabel(m_preferenceContentListWidget);
    //headSpaceItem->setSizeHint(QSize(m_preferenceContentListWidget->width(), 10));
    //m_preferenceContentListWidget->setItemWidget(headSpaceItem, headSpace);

    // 生成设置项
    for (PreferenceItem* item : m_preferenceItemList)
        item->generatePreferenceItem(m_preferenceContentListWidget, m_preferenceMap);

    // 设置项逻辑
    QString value;
    PreferenceHelper::getHelper()->getPreferenceValue("recycleBin", value);
    if (value == "on")
        m_preferenceMap.preferenceLineEditMap["retentionPeriod"]->setEnabled(true);
    else
        m_preferenceMap.preferenceLineEditMap["retentionPeriod"]->setEnabled(false);


    // 不可选定
    for (int i = 0; i < m_preferenceContentListWidget->count(); ++i)
    {
        QListWidgetItem* item = m_preferenceContentListWidget->item(i);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    }
}

// 槽函数
void PreferenceView::checkIsLineEditNull()
{
    QString text = m_searchLineEdit->text().trimmed();
    if (text.length()) switchOverSearchButton(1);
    else switchOverSearchButton(0);
}

void PreferenceView::deleteSearchText()
{
    m_searchLineEdit->clear();
}


// 私有函数
void PreferenceView::showpreference(QTreeWidget* treeWidget, QTreeWidgetItem* item)
{
    item->setHidden(false);
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        showpreference(treeWidget, child);
    }
}

void PreferenceView::notExpandpreference()
{
    for (int i = 0; i < m_preferenceTreeWidget->invisibleRootItem()->childCount(); ++i)
    {
        m_preferenceTreeWidget->invisibleRootItem()->child(i)->setExpanded(false);
    }
}

void PreferenceView::switchOverSearchButton(bool msg)
{
    if (msg)
    {
        m_searchButton->setIcon(QIcon(":/icon/close_bla.ico"));
        m_searchButtonHoverWatcher->setResource(QString(":/icon/close_bla.ico"), QString(":/icon/close_blu.ico"));
        m_searchButton->disconnect();
        connect(m_searchButton, &QPushButton::clicked, this, &PreferenceView::deleteSearchText);
        searchpreference(); // 一旦有文字输入，总是自动开始寻找匹配项
    }
    else
    {
        m_searchButton->setIcon(QIcon(":/icon/search_bla.ico"));
        m_searchButtonHoverWatcher->setResource(QString(":/icon/search_bla.ico"), QString(":/icon/search_blu.ico"));
        m_searchButton->disconnect();
        connect(m_searchButton, &QPushButton::clicked, this, &PreferenceView::searchpreference);
        showpreference(m_preferenceTreeWidget, m_preferenceTreeWidget->invisibleRootItem()); // 一旦为空，则显示所有项
        m_preferenceTreeWidget->setVisible(true);
        m_preferenceTreeStackedWidget->setCurrentIndex(0);
        notExpandpreference();
    }
}

void PreferenceView::searchpreference()
{
    QString searchText = m_searchLineEdit->text().trimmed();
    notExpandpreference();
    if (searchText.length())
    {
        QTreeWidgetItem* item = m_preferenceTreeWidget->invisibleRootItem();
        bool searchFlag = false;
        showpreference(m_preferenceTreeWidget, m_preferenceTreeWidget->invisibleRootItem());
        // 一级列表
        for (int i = 0; i < item->childCount(); ++i)
        {
            QTreeWidgetItem* child = item->child(i);
            if (!child->text(0).contains(searchText, Qt::CaseInsensitive)) // 如果没有包含关键字，查询二级列表
            {
                // 二级列表
                for (int j = 0; j < child->childCount(); ++j)
                {
                    QTreeWidgetItem* grandchild = child->child(j);
                    if (!grandchild->text(0).contains(searchText, Qt::CaseInsensitive)) grandchild->setHidden(true);
                    else searchFlag = true;
                }
                // 如果这一级列表下的二级列表都被隐藏，那么这一级列表也被隐藏（只要有一个没有隐藏，那么就不隐藏这一级列表）
                bool notHiddenFlag = false;
                for (int j = 0; j < child->childCount(); ++j)
                    if (!child->child(j)->isHidden()) notHiddenFlag = true;
                if (!notHiddenFlag) child->setHidden(true);
                else child->setExpanded(true);
            }
            else // 如果包含，继续查询二级列表决定是否展开（只要有一个没有隐藏，那么这一级列表都应该展开）
            {
                searchFlag = true;
                bool expandedFlag = false;
                for (int j = 0; j < child->childCount(); ++j)
                {
                    QTreeWidgetItem* grandchild = child->child(j);
                    if (!grandchild->text(0).contains(searchText, Qt::CaseInsensitive)) grandchild->setHidden(true);
                }
                for (int j = 0; j < child->childCount(); ++j)
                    if (!child->child(j)->isHidden()) expandedFlag = true;
                child->setExpanded(expandedFlag);
                // 无论如何，最后都不隐藏二级列表
                for (int j = 0; j < child->childCount(); ++j) child->child(j)->setHidden(false);
            }
        }
        m_preferenceTreeStackedWidget->setCurrentIndex(searchFlag ? 0 : 1);
    }
}

void PreferenceView::adjustSizeHint()
{
    if (m_preferenceMap.hintItemLabelMap.size())
    {
        for (QListWidgetItem* item : m_preferenceMap.hintItemLabelMap.keys()) {
            QLabel* label = m_preferenceMap.hintItemLabelMap.value(item);
            QFontMetrics fontMetrics(label->font());
            int newHeight = fontMetrics.boundingRect(QRect(0, 0, label->width(), fontMetrics.height()), Qt::TextWordWrap, label->text()).height();
            label->setFixedHeight(newHeight);
            item->setSizeHint(QSize(item->sizeHint().width(), newHeight));
        }
    }
}

void PreferenceView::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    // 设置页表单
    adjustSizeHint();
}