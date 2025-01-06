#include "View_Settings.h"

SettingsView::SettingsView(QWidget* parent) :
	QWidget(parent)
{
	setupUi();
}

SettingsView::~SettingsView()
{
    for (SettingItem* item : m_settingsItemList)
    {
        delete item;
    }
}

void SettingsView::setupUi()
{
    this->setObjectName("settings");
    m_settingsLayout = new QHBoxLayout(this);
    m_settingsLayout->setSpacing(0);
    m_settingsLayout->setContentsMargins(10, 10, 10, 10);

    // 左栏
    m_settingsLeftWidget = new QWidget(this);
    m_settingsLeftWidget->setObjectName("settingsLeftWidget");
    m_settingsLeftWidget->setFixedWidth(200);
    m_settingsLeftLayout = new QVBoxLayout(m_settingsLeftWidget);
    m_settingsLeftLayout->setObjectName("settingsLeftLayout");
    m_settingsLeftLayout->setSpacing(0);
    m_settingsLeftLayout->setContentsMargins(0, 0, 0, 0);

    // 搜索区域
    m_searchLineEdit = new QLineEdit(m_settingsLeftWidget);
    m_searchLineEdit->setFixedHeight(30);
    m_searchLineEdit->setObjectName("searchLineEdit");
    m_searchLineEdit->setPlaceholderText(searchText);
    m_searchLineEdit->setFont(QFont("Hind Siliguri", 13));
    QPalette searchPalette = m_searchLineEdit->palette();
    searchPalette.setColor(searchPalette.PlaceholderText, QColor("#cccccc"));
    m_searchButton = new QPushButton(m_searchLineEdit);
    m_searchButton->setObjectName("searchButton");
    m_searchButton->setIcon(QIcon(":/icon/search_bla.png"));
    m_searchButton->setCursor(Qt::ArrowCursor);
    QWidgetAction* searchAction = new QWidgetAction(m_searchLineEdit);
    searchAction->setDefaultWidget(m_searchButton);
    m_searchLineEdit->addAction(searchAction, QLineEdit::TrailingPosition);
    m_searchButtonHoverWatcher = new ButtonHoverWatcher(QString(":/icon/search_bla.png"), QString(":/icon/search_blu.png"), this);
    m_searchButton->installEventFilter(m_searchButtonHoverWatcher);

    // 目录
    m_settingsTreeStackedWidget = new QStackedWidget(m_settingsLeftWidget);
    m_settingsTreeWidget = new QTreeWidget(m_settingsTreeStackedWidget);
    m_settingsTreeWidget->setHeaderHidden(true);
    formTree();
    m_settingsTreeWidget->setFont(QFont("Hind Siliguri", 13));
    m_searchsettingsNullLabel = new QLabel("No matches were found.", m_settingsTreeStackedWidget);
    m_searchsettingsNullLabel->setVisible(false); // 默认不显示“未找到匹配项”
    m_searchsettingsNullLabel->setFont(QFont("Hind Siliguri", 13));
    m_searchsettingsNullLabel->setAlignment(Qt::AlignTop);
    m_settingsTreeStackedWidget->addWidget(m_settingsTreeWidget);
    m_settingsTreeStackedWidget->addWidget(m_searchsettingsNullLabel);
    m_settingsTreeStackedWidget->setCurrentIndex(0);

    m_settingsLeftLayout->addWidget(m_searchLineEdit);
    m_settingsLeftLayout->addWidget(m_settingsTreeStackedWidget);

    // 右栏
    m_settingsRightWidget = new QWidget(this);
    m_settingsRightWidget->setObjectName("settingsRightWidget");
    m_settingsRightLayout = new QVBoxLayout(m_settingsRightWidget);
    m_settingsRightLayout->setObjectName("settingsRightLayout");
    m_settingsRightLayout->setSpacing(0);
    m_settingsRightLayout->setContentsMargins(10, 0, 0, 0);

    m_settingsContentListWidget = new QListWidget(m_settingsRightWidget);
    formContentList();
    m_settingsContentListWidget->setSelectionRectVisible(false);
    m_settingsRightLayout->addWidget(m_settingsContentListWidget);

    m_settingsLayout->addWidget(m_settingsLeftWidget);
    m_settingsLayout->addWidget(m_settingsRightWidget);
}

void SettingsView::formTree()
{
    // 一级目录
    QTreeWidgetItem* item1 = new QTreeWidgetItem(m_settingsTreeWidget);
    item1->setText(0, "Common");
    item1->setIcon(0, QIcon(":/icon/common.png"));
    m_settingsTreeWidget->addTopLevelItem(item1);
    QTreeWidgetItem* item2 = new QTreeWidgetItem(m_settingsTreeWidget);
    item2->setText(0, "Task");
    item2->setIcon(0, QIcon(":/icon/export.png"));
    m_settingsTreeWidget->addTopLevelItem(item2);

    // 二级目录
    QTreeWidgetItem* item1_1 = new QTreeWidgetItem(item1);
    item1_1->setText(0, "Appearance");
    item1_1->setIcon(0, QIcon(":/icon/appearance.png"));
    QTreeWidgetItem* item1_2 = new QTreeWidgetItem(item1);
    item1_2->setText(0, "Country/Region");
    item1_2->setIcon(0, QIcon(":/icon/country_region.png"));
    QTreeWidgetItem* item2_1 = new QTreeWidgetItem(item2);
    item2_1->setText(0, "Recycle Bin");
    item2_1->setIcon(0, QIcon(":/icon/country_region.png"));
}

void SettingsView::formContentList()
{
    // HeadSpace
    QListWidgetItem* headSpaceItem = new QListWidgetItem(m_settingsContentListWidget);
    QLabel* headSpace = new QLabel(m_settingsContentListWidget);

    headSpaceItem->setSizeHint(QSize(m_settingsContentListWidget->width(), 10));
    m_settingsContentListWidget->setItemWidget(headSpaceItem, headSpace);
    for (SettingItem* item : m_settingsItemList)
    {
        item->generateSettingItem(m_settingsContentListWidget, m_settingMap);
    }

    // 不可选定
    for (int i = 0; i < m_settingsContentListWidget->count(); ++i)
    {
        QListWidgetItem* item = m_settingsContentListWidget->item(i);
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    }
}

// 槽函数
void SettingsView::checkIsLineEditNull()
{
    QString text = m_searchLineEdit->text().trimmed();
    if (text.length()) switchOverSearchButton(1);
    else switchOverSearchButton(0);
}

void SettingsView::deleteSearchText()
{
    m_searchLineEdit->clear();
}


// 私有函数
void SettingsView::showSettings(QTreeWidget* treeWidget, QTreeWidgetItem* item)
{
    item->setHidden(false);
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        showSettings(treeWidget, child);
    }
}

void SettingsView::notExpandSettings()
{
    for (int i = 0; i < m_settingsTreeWidget->invisibleRootItem()->childCount(); ++i)
    {
        m_settingsTreeWidget->invisibleRootItem()->child(i)->setExpanded(false);
    }
}

void SettingsView::switchOverSearchButton(bool msg)
{
    if (msg)
    {
        m_searchButton->setIcon(QIcon(":/icon/close_bla.png"));
        m_searchButtonHoverWatcher->setResource(QString(":/icon/close_bla.png"), QString(":/icon/close_blu.png"));
        m_searchButton->disconnect();
        connect(m_searchButton, &QPushButton::clicked, this, &SettingsView::deleteSearchText);
        searchSettings(); // 一旦有文字输入，总是自动开始寻找匹配项
    }
    else
    {
        m_searchButton->setIcon(QIcon(":/icon/search_bla.png"));
        m_searchButtonHoverWatcher->setResource(QString(":/icon/search_bla.png"), QString(":/icon/search_blu.png"));
        m_searchButton->disconnect();
        connect(m_searchButton, &QPushButton::clicked, this, &SettingsView::searchSettings);
        showSettings(m_settingsTreeWidget, m_settingsTreeWidget->invisibleRootItem()); // 一旦为空，则显示所有项
        m_settingsTreeWidget->setVisible(true);
        m_settingsTreeStackedWidget->setCurrentIndex(0);
        notExpandSettings();
    }
}

void SettingsView::searchSettings()
{
    QString searchText = m_searchLineEdit->text().trimmed();
    notExpandSettings();
    if (searchText.length())
    {
        QTreeWidgetItem* item = m_settingsTreeWidget->invisibleRootItem();
        bool searchFlag = false;
        showSettings(m_settingsTreeWidget, m_settingsTreeWidget->invisibleRootItem());
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
        m_settingsTreeStackedWidget->setCurrentIndex(searchFlag ? 0 : 1);
    }
}

void SettingsView::adjustSizeHint()
{
    if (m_settingMap.hintItemLabelMap.size())
    {
        for (QListWidgetItem* const &item : m_settingMap.hintItemLabelMap.keys()) {
            QLabel* label = m_settingMap.hintItemLabelMap.value(item);
            QFontMetrics fontMetrics(label->font());
            int newHeight = fontMetrics.boundingRect(QRect(0, 0, label->width(), fontMetrics.height()), Qt::TextWordWrap, label->text()).height();
            label->setFixedHeight(newHeight);
            item->setSizeHint(QSize(item->sizeHint().width(), newHeight));
        }
    }
}

void SettingsView::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    // 设置页表单
    adjustSizeHint();
}