#include "Settings.h"
#include <math.h>
#include <QTextLayout>

Settings::Settings(QWidget* parent) :
	QWidget(parent)
{
	ui.setupUi(this);

    SettingsHelper helper;
    ui.themeBox->setCurrentText(helper.readSettings("theme"));
    connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &Settings::checkIsLineEditNull);
    connect(ui.searchButton, &QPushButton::clicked, this, &Settings::searchSettings);
    connect(ui.settingsTreeWidget, &QTreeWidget::itemClicked, [&](QTreeWidgetItem* item, int column) {item->setExpanded(!item->isExpanded()); });
    connect(ui.settingsTreeWidget, &QTreeWidget::itemDoubleClicked, [&](QTreeWidgetItem* item, int column)
        {
            int row = ui.settingsItemRowMap[item->text(column)];
            ui.settingsContentListWidget->scrollToItem(ui.settingsContentListWidget->item(row), QAbstractItemView::PositionAtTop);
        });
    connect(ui.themeBox, &QComboBox::currentIndexChanged, [&](int index)
        {
            SettingsHelper helper;
            helper.writeSettings("theme", ui.themeBox->currentText());
            emit SignalApplyTheme(ui.themeBox->currentText());
        });
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

// ˽�к���
void Settings::showSettings(QTreeWidget* treeWidget, QTreeWidgetItem* item)
{
    item->setHidden(false);
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        showSettings(treeWidget, child);
    }
}

void Settings::notExpandSettings(QTreeWidget* treeWidget)
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
        ui.searchButton->setIcon(QIcon("res/ico/close_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/ico/close_bla.png"), QString("res/ico/close_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Settings::deleteSearchText);
        searchSettings(); // һ�����������룬�����Զ���ʼѰ��ƥ����
    }
    else
    {
        ui.searchButton->setIcon(QIcon("res/ico/search_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/ico/search_bla.png"), QString("res/ico/search_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Settings::searchSettings);
        showSettings(ui.settingsTreeWidget, ui.settingsTreeWidget->invisibleRootItem()); // һ��Ϊ�գ�����ʾ������
        ui.settingsTreeWidget->setVisible(true);
        ui.settingsTreeStackedWidget->setCurrentIndex(0);
        notExpandSettings(ui.settingsTreeWidget);
    }
}

void Settings::searchSettings()
{
    QString searchText = ui.searchLineEdit->text().trimmed();
    notExpandSettings(ui.settingsTreeWidget);
    if (searchText.length())
    {
        QTreeWidgetItem* item = ui.settingsTreeWidget->invisibleRootItem();
        bool searchFlag = false;
        showSettings(ui.settingsTreeWidget, ui.settingsTreeWidget->invisibleRootItem());
        // һ���б�
        for (int i = 0; i < item->childCount(); ++i)
        {
            QTreeWidgetItem* child = item->child(i);
            if (!child->text(0).contains(searchText, Qt::CaseInsensitive)) // ���û�а����ؼ��֣���ѯ�����б�
            {
                // �����б�
                for (int j = 0; j < child->childCount(); ++j)
                {
                    QTreeWidgetItem* grandchild = child->child(j);
                    if (!grandchild->text(0).contains(searchText, Qt::CaseInsensitive)) grandchild->setHidden(true);
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
                    if (!grandchild->text(0).contains(searchText, Qt::CaseInsensitive)) grandchild->setHidden(true);
                }
                for (int j = 0; j < child->childCount(); ++j)
                    if (!child->child(j)->isHidden()) expandedFlag = true;
                child->setExpanded(expandedFlag);
                // ������Σ���󶼲����ض����б�
                for (int j = 0; j < child->childCount(); ++j) child->child(j)->setHidden(false);
            }
        }
        ui.settingsTreeStackedWidget->setCurrentIndex(searchFlag ? 0 : 1);
    }
}

void Settings::adjustSizeHint()
{
    if (ui.hintItemLabelMap.size())
    {
        for (auto &[item, label] : ui.hintItemLabelMap) {
            QFontMetrics fontMetrics(label->font());
            int newHeight = fontMetrics.boundingRect(QRect(0, 0, label->width(), fontMetrics.height()), Qt::TextWordWrap, label->text()).height();
            label->setFixedHeight(newHeight);
            item->setSizeHint(QSize(item->sizeHint().width(), newHeight));
        }
    }
}

void Settings::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    // ����ҳ��
    adjustSizeHint();
}