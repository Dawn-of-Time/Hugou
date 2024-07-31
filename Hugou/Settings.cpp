#include "Settings.h"

Settings::Settings(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	
	// 配置读取和应用
	//QSettings settings("res/conf.ini", QSettings::IniFormat);
    connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &Settings::checkIsLineEditNull);
    connect(ui.searchButton, &QPushButton::clicked, this, &Settings::search);
    connect(ui.settingsTreeWidget, &QTreeWidget::itemClicked, [&](QTreeWidgetItem* item, int column) {item->setExpanded(!item->isExpanded()); });
    connect(ui.settingsTreeWidget, &QTreeWidget::itemDoubleClicked, [&](QTreeWidgetItem* item, int column)
        {
            int row = ui.settingsItemRowMap[item->text(column)];
            ui.settingsContentListWidget->scrollToItem(ui.settingsContentListWidget->item(row), QAbstractItemView::PositionAtTop);
        });
    connect(ui.themeBox, &QComboBox::currentIndexChanged, [&](int index)
        {
            QString oldsetting = settingsCommonMap["theme"];
            settingsCommonMap["theme"] = ui.themeBox->currentText();
            //if (!setting->applySetting(this, "themeBox", oldsetting)) raiseSavingSettingError();
        });
}

bool Settings::searchSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item, QString text)
{
    bool searchFlag = false;
    showSetting(treeWidget, treeWidget->invisibleRootItem());
    // 一级列表
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        if (!child->text(0).contains(text, Qt::CaseInsensitive)) // 如果没有包含关键字，查询二级列表
        {
            // 二级列表
            for (int j = 0; j < child->childCount(); ++j)
            {
                QTreeWidgetItem* grandchild = child->child(j);
                if (!grandchild->text(0).contains(text, Qt::CaseInsensitive)) grandchild->setHidden(true);
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
                if (!grandchild->text(0).contains(text, Qt::CaseInsensitive)) grandchild->setHidden(true);
            }
            for (int j = 0; j < child->childCount(); ++j)
                if (!child->child(j)->isHidden()) expandedFlag = true;
            child->setExpanded(expandedFlag);
            // 无论如何，最后都不隐藏二级列表
            for (int j = 0; j < child->childCount(); ++j) child->child(j)->setHidden(false);
        }
    }
    return searchFlag;
}

void Settings::showSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item)
{
    item->setHidden(false);
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        showSetting(treeWidget, child);
    }
}

void Settings::notExpandSetting(QTreeWidget* treeWidget)
{
    for (int i = 0; i < treeWidget->invisibleRootItem()->childCount(); ++i)
    {
        treeWidget->invisibleRootItem()->child(i)->setExpanded(false);
    }
}

void Settings::switchOverSearchButton(bool msg)
{
    if (msg)
    {
        ui.searchButton->setIcon(QIcon("res/close_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/close_bla.png"), QString("res/close_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Settings::deleteSearchText);
        search(); // 一旦有文字输入，总是自动开始寻找匹配项
    }
    else
    {
        ui.searchButton->setIcon(QIcon("res/search_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/search_bla.png"), QString("res/search_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Settings::search);
        showSetting(ui.settingsTreeWidget, ui.settingsTreeWidget->invisibleRootItem()); // 一旦为空，则显示所有项
        ui.settingsTreeWidget->setVisible(true);
        ui.settingsTreeStackedWidget->setCurrentIndex(0);
        notExpandSetting(ui.settingsTreeWidget);
    }
}

void Settings::search()
{
    QSettings settings("res/conf.ini", QSettings::IniFormat);
    QString searchText = ui.searchLineEdit->text().trimmed();
    notExpandSetting(ui.settingsTreeWidget);
    if (searchText.length())
    {
        int searchNum = searchSetting(ui.settingsTreeWidget, ui.settingsTreeWidget->invisibleRootItem(), searchText);
        ui.settingsTreeStackedWidget->setCurrentIndex(searchNum ? 0 : 1);
    }
}

// 槽函数
void Settings::checkIsLineEditNull()
{
    QString text = ui.searchLineEdit->text().trimmed();
    if (text.length()) switchOverSearchButton(1);
    else switchOverSearchButton(0);
}

void Settings::deleteSearchText()
{
    ui.searchLineEdit->clear();
}