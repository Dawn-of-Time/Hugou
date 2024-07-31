#include "Settings.h"

Settings::Settings(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	
	// ���ö�ȡ��Ӧ��
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
    // һ���б�
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        if (!child->text(0).contains(text, Qt::CaseInsensitive)) // ���û�а����ؼ��֣���ѯ�����б�
        {
            // �����б�
            for (int j = 0; j < child->childCount(); ++j)
            {
                QTreeWidgetItem* grandchild = child->child(j);
                if (!grandchild->text(0).contains(text, Qt::CaseInsensitive)) grandchild->setHidden(true);
                else searchFlag = true;
            }
            // �����һ���б��µĶ����б������أ���ô��һ���б�Ҳ�����أ�ֻҪ��һ��û�����أ���ô�Ͳ�������һ���б�
            bool notHiddenFlag = false;
            for (int j = 0; j < child->childCount(); ++j)
                if (!child->child(j)->isHidden()) notHiddenFlag = true;
            if (!notHiddenFlag) child->setHidden(true);
            else child->setExpanded(true);
        }
        else // ���������������ѯ�����б�����Ƿ�չ����ֻҪ��һ��û�����أ���ô��һ���б�Ӧ��չ����
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
            // ������Σ���󶼲����ض����б�
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
        search(); // һ�����������룬�����Զ���ʼѰ��ƥ����
    }
    else
    {
        ui.searchButton->setIcon(QIcon("res/search_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/search_bla.png"), QString("res/search_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Settings::search);
        showSetting(ui.settingsTreeWidget, ui.settingsTreeWidget->invisibleRootItem()); // һ��Ϊ�գ�����ʾ������
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

// �ۺ���
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