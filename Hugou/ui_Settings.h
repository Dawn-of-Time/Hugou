#pragma once

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QComboBox>
#include <QWidgetAction>
#include <QFile>
#include "ButtonHoverWatcher.h"
#include "Const.h"

class Ui_Settings
{
public:
    QHBoxLayout* settingsLayout;
    QWidget* settingsLeftWidget;
    QVBoxLayout* settingsLeftLayout;
    QLineEdit* searchLineEdit;
    QPushButton* searchButton;
    QPushButton* searchDeletedButton;
    ButtonHoverWatcher* searchButtonHoverWatcher;
    ButtonHoverWatcher* searchDeletedButtonHoverWatcher;
    QStackedWidget* settingsTreeStackedWidget;
    QVBoxLayout* settingsTreeLayout;
    QTreeWidget* settingsTreeWidget;
    QLabel* searchsettingsNullLabel;
    QWidget* settingsRightWidget;
    QVBoxLayout* settingsRightLayout;
    QListWidget* settingsContentListWidget;
    QComboBox* themeBox;
    QComboBox* languageBox;
    QPushButton* savePathButton;
    QLineEdit* savePathLineEdit;
    std::map<QString, int> settingsItemRowMap;

    void setupUi(QWidget* settings)
    {
        settings->setObjectName("settings");
        settingsLayout = new QHBoxLayout(settings);
        settingsLayout->setSpacing(0);
        settingsLayout->setContentsMargins(10, 10, 10, 10);

        // 左栏
        settingsLeftWidget = new QWidget(settings);
        settingsLeftWidget->setObjectName("settingsLeftWidget");
        settingsLeftWidget->setFixedWidth(200);
        settingsLeftLayout = new QVBoxLayout(settingsLeftWidget);
        settingsLeftLayout->setObjectName("settingsLeftLayout");
        settingsLeftLayout->setSpacing(0);
        settingsLeftLayout->setContentsMargins(0, 0, 0, 0);

        // 搜索区域
        searchLineEdit = new QLineEdit(settingsLeftWidget);
        searchLineEdit->setFixedHeight(30);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setPlaceholderText(searchText);
        searchLineEdit->setFont(QFont("Hind Siliguri", 13));
        QPalette searchPalette = searchLineEdit->palette();
        searchPalette.setColor(searchPalette.PlaceholderText, QColor("#cccccc"));
        searchButton = new QPushButton(searchLineEdit);
        searchButton->setObjectName("searchButton");
        searchButton->setIcon(QIcon("res/ico/search_bla.png"));
        searchButton->setCursor(Qt::ArrowCursor);
        QWidgetAction* searchAction = new QWidgetAction(searchLineEdit);
        searchAction->setDefaultWidget(searchButton);
        searchLineEdit->addAction(searchAction, QLineEdit::TrailingPosition);
        searchButtonHoverWatcher = new ButtonHoverWatcher(QString("res/ico/search_bla.png"), QString("res/ico/search_blu.png"), settings);
        searchButton->installEventFilter(searchButtonHoverWatcher);

        // 目录
        settingsTreeStackedWidget = new QStackedWidget(settingsLeftWidget);
        settingsTreeWidget = new QTreeWidget(settingsTreeStackedWidget);
        settingsTreeWidget->setHeaderHidden(true);
        settingsTreeWidget = formTree(settingsTreeWidget);
        settingsTreeWidget->setFont(QFont("Hind Siliguri", 13));
        searchsettingsNullLabel = new QLabel("No matches were found.", settingsTreeStackedWidget);
        searchsettingsNullLabel->setVisible(false); // 默认不显示“未找到匹配项”
        searchsettingsNullLabel->setFont(QFont("Hind Siliguri", 13));
        searchsettingsNullLabel->setAlignment(Qt::AlignTop);
        settingsTreeStackedWidget->addWidget(settingsTreeWidget);
        settingsTreeStackedWidget->addWidget(searchsettingsNullLabel);
        settingsTreeStackedWidget->setCurrentIndex(0);

        settingsLeftLayout->addWidget(searchLineEdit);
        settingsLeftLayout->addWidget(settingsTreeStackedWidget);

        // 右栏
        settingsRightWidget = new QWidget(settings);
        settingsRightWidget->setObjectName("settingsRightWidget");
        settingsRightLayout = new QVBoxLayout(settingsRightWidget);
        settingsRightLayout->setObjectName("settingsRightLayout");
        settingsRightLayout->setSpacing(0);
        settingsRightLayout->setContentsMargins(10, 0, 0, 0);

        settingsContentListWidget = new QListWidget(settingsRightWidget);
        settingsContentListWidget = formContentList(settingsContentListWidget);
        settingsContentListWidget->setSelectionRectVisible(false);
        settingsRightLayout->addWidget(settingsContentListWidget);

        settingsLayout->addWidget(settingsLeftWidget);
        settingsLayout->addWidget(settingsRightWidget);

        QFile styleFile("res/style/Default/settings.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        settings->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }

    QTreeWidget* formTree(QTreeWidget* settingsTreeWidget)
    {
        // 一级目录
        QTreeWidgetItem* item1 = new QTreeWidgetItem(settingsTreeWidget);
        item1->setText(0, "Common");
        item1->setIcon(0, QIcon("res/ico/common.png"));
        settingsTreeWidget->addTopLevelItem(item1);
        QTreeWidgetItem* item2 = new QTreeWidgetItem(settingsTreeWidget);
        item2->setText(0, "Export");
        item2->setIcon(0, QIcon("res/ico/export.png"));
        settingsTreeWidget->addTopLevelItem(item2);

        // 二级目录
        QTreeWidgetItem* item1_1 = new QTreeWidgetItem(item1);
        item1_1->setText(0, "Appearance");
        item1_1->setIcon(0, QIcon("res/ico/appearance.png"));
        QTreeWidgetItem* item1_2 = new QTreeWidgetItem(item1);
        item1_2->setText(0, "Country/Region");
        item1_2->setIcon(0, QIcon("res/ico/country_region.png"));

        return settingsTreeWidget;
    }

    QListWidget* formContentList(QListWidget* settingsContentListWidget)
    {
        // HeadSpace
        QListWidgetItem* headSpaceItem = new QListWidgetItem(settingsContentListWidget);
        QLabel* headSpace = new QLabel(settingsContentListWidget);
        
        headSpaceItem->setSizeHint(QSize(settingsContentListWidget->width(), 10));
        settingsContentListWidget->setItemWidget(headSpaceItem, headSpace);

        // 1-General
        QListWidgetItem* item1 = new QListWidgetItem(settingsContentListWidget);
        firstNodesettingsItem(item1, "Common");
        // 1.1-Appearance
        QListWidgetItem* item1_1 = new QListWidgetItem(settingsContentListWidget);
        secondNodesettingsItem(item1_1, "Appearance");
        // 1.1.1-Theme
        QListWidgetItem* item1_1_1 = new QListWidgetItem(settingsContentListWidget);
        thirdNodesettingsItem(item1_1_1, "Theme");
        // Theme Hint
        QListWidgetItem* hint1 = new QListWidgetItem(settingsContentListWidget);
        hintsettingsItem(hint1, "I will be launching the theme preview feature in the near future.");
        // 1.1.1.1-themeBox
        QListWidgetItem* item1_1_1_1 = new QListWidgetItem(settingsContentListWidget);
        themeBox = contentNodeComboboxsettingsItem(item1_1_1_1, "themeBox", themeList);
        // Space1
        QListWidgetItem* spaceItem1 = new QListWidgetItem(settingsContentListWidget);
        sectionSpaceItem(spaceItem1);
        // 1.2-Country/Region
        QListWidgetItem* item1_2 = new QListWidgetItem(settingsContentListWidget);
        secondNodesettingsItem(item1_2, "Country/Region");
        // 1.2.1-Language
        QListWidgetItem* item1_2_1 = new QListWidgetItem(settingsContentListWidget);
        thirdNodesettingsItem(item1_2_1, "Language");
        // Language Hint
        QListWidgetItem* hint2 = new QListWidgetItem(settingsContentListWidget);
        hintsettingsItem(hint2, "More and more languages are getting support. The language currently in the pipeline is: Chinese.");
        // 1.2.1.1-languageBox
        QListWidgetItem* item1_2_1_1 = new QListWidgetItem(settingsContentListWidget);
        languageBox = contentNodeComboboxsettingsItem(item1_2_1_1, "languageBox", languageList);
        // Space2
        QListWidgetItem* spaceItem2 = new QListWidgetItem(settingsContentListWidget);
        chapterSpaceItem(spaceItem2);

        // 2-Export
        QListWidgetItem* item2 = new QListWidgetItem(settingsContentListWidget);
        firstNodesettingsItem(item2, "Export");
        // 2.1-Save
        QListWidgetItem* item2_1 = new QListWidgetItem(settingsContentListWidget);
        secondNodesettingsItem(item2_1, "Save");
        // 2.1.1-Default Save Path
        QListWidgetItem* item2_1_1 = new QListWidgetItem(settingsContentListWidget);
        thirdNodesettingsItem(item2_1_1, "Default Save Path");
        // Save Path Hint
        QListWidgetItem* hint3 = new QListWidgetItem(settingsContentListWidget);
        hintsettingsItem(hint3, "This feature is to be developed.");
        // 2.1.1.1-save path lineedit
        QListWidgetItem* item2_1_1_1 = new QListWidgetItem(settingsContentListWidget);
        savePathLineEdit = contentNodeLineEditsettingsItem(item2_1_1_1);
        savePathButton = new QPushButton(savePathLineEdit);
        savePathButton->setObjectName("savePathButton");
        savePathButton->setIcon(QIcon("res/ico/browse_bla.png"));
        savePathButton->setCursor(Qt::ArrowCursor);
        QWidgetAction* savePathAction = new QWidgetAction(savePathLineEdit);
        savePathAction->setDefaultWidget(savePathButton);
        savePathLineEdit->addAction(savePathAction, QLineEdit::TrailingPosition);
        ButtonHoverWatcher* savePathButtonHoverWatcher = new ButtonHoverWatcher(QString("res/ico/browse_bla.png"), QString("res/ico/browse_blu.png"));
        savePathButton->installEventFilter(savePathButtonHoverWatcher);

        // TailSpace
        QListWidgetItem* tailSpaceItem = new QListWidgetItem(settingsContentListWidget);
        QLabel* tailSpace = new QLabel(settingsContentListWidget);
        headSpaceItem->setSizeHint(QSize(settingsContentListWidget->width(), 15));
        settingsContentListWidget->setItemWidget(tailSpaceItem, tailSpace);

        // 不可选定
        for (int i = 0; i < settingsContentListWidget->count(); ++i)
        {
            QListWidgetItem* item = settingsContentListWidget->item(i);
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        }
        return settingsContentListWidget;
    }

    void firstNodesettingsItem(QListWidgetItem* item, QString settingsName)
    {
        QString firstNodeStyleSheet = "QLabel {border-width: 0 0 0 5px; border-style: solid; border-color: black; padding-left: 2px}";
        QFont firstNodeFont = QFont("Hind Siliguri", 22);
        QLabel* label = new QLabel(settingsName, settingsContentListWidget);
        label->setFont(firstNodeFont);
        label->setStyleSheet(firstNodeStyleSheet);
        item->setSizeHint(label->sizeHint());
        settingsContentListWidget->setItemWidget(item, label);
        settingsItemRowMap.insert({ settingsName, settingsContentListWidget->indexFromItem(item).row() });
    }

    void secondNodesettingsItem(QListWidgetItem* item, QString settingsName)
    {
        QString secondNodeStyleSheet = "QLabel {margin-left: 15px}";
        QFont secondNodeFont = QFont("Hind Siliguri", 16);
        QLabel* label = new QLabel(settingsName, settingsContentListWidget);
        label->setFont(secondNodeFont);
        label->setStyleSheet(secondNodeStyleSheet);
        item->setSizeHint(label->sizeHint());
        settingsContentListWidget->setItemWidget(item, label);
        settingsItemRowMap.insert({ settingsName, settingsContentListWidget->indexFromItem(item).row() });
    }

    void thirdNodesettingsItem(QListWidgetItem* item, QString settingsName)
    {
        QString thirdNodeStyleSheet = "QLabel {margin-left: 20px}";
        QFont thirdNodeFont = QFont("Hind Siliguri Light", 14);
        QLabel* label = new QLabel(settingsName, settingsContentListWidget);
        label->setFont(thirdNodeFont);
        label->setStyleSheet(thirdNodeStyleSheet);
        item->setSizeHint(label->sizeHint());
        settingsContentListWidget->setItemWidget(item, label);
        settingsItemRowMap.insert({ settingsName, settingsContentListWidget->indexFromItem(item).row() });
    }

    QComboBox* contentNodeComboboxsettingsItem(QListWidgetItem* item, QString objectName, QStringList comboboxList)
    {
        QString contentStyleSheet = "QLabel {margin-left: 20px}";
        QString contentComboBoxStyleSheet = ".QComboBox {margin-left: 15px}";
        QFont contentFont = QFont("Hind Siliguri Light", 12);
        QLabel* label = new QLabel(settingsContentListWidget);
        label->setStyleSheet(contentStyleSheet);
        QComboBox* comboBox = new QComboBox(label);
        comboBox->setObjectName(objectName);
        comboBox->move(20, 0);
        comboBox->addItems(comboboxList);
        comboBox->setFont(contentFont);
        comboBox->setFixedSize(200, 30);
        //ComboboxWheelWatcher* comboBoxWheelWatcher = new ComboboxWheelWatcher(item->listWidget());
        //comboBox->installEventFilter(comboBoxWheelWatcher);
        item->setSizeHint(QSize(settingsContentListWidget->width(), 30));
        settingsContentListWidget->setItemWidget(item, label);
        return comboBox;
    }

    QLineEdit* contentNodeLineEditsettingsItem(QListWidgetItem* item)
    {
        QString contentStyleSheet = "QLabel {margin-left: 20px}";
        QString contentLineEditStyleSheet = ".QLineEdit {margin-left: 15px; border: none }";
        QFont contentFont = QFont("Hind Siliguri Light", 12);
        QLabel* label = new QLabel(settingsContentListWidget);
        label->setStyleSheet(contentStyleSheet);
        QLineEdit* lineEdit = new QLineEdit(label);
        lineEdit->move(20, 0);
        lineEdit->setFont(contentFont);
        lineEdit->setFixedHeight(30);
        item->setSizeHint(QSize(settingsContentListWidget->width(), 30));
        settingsContentListWidget->setItemWidget(item, label);
        return lineEdit;
    }

    void hintsettingsItem(QListWidgetItem* item, QString hint)
    {
        QString hintStyleSheet = "QLabel {margin-left: 20px; color: #696969; padding: 0px}";
        QFont hintFont = QFont("Hind Siliguri Light", 12);
        QLabel* label = new QLabel(hint, settingsContentListWidget);
        label->setFont(hintFont);
        label->setStyleSheet(hintStyleSheet);
        label->setWordWrap(true);
        label->adjustSize();
        item->setSizeHint(QSize(label->sizeHint().width(), label->sizeHint().height() - 20));
        settingsContentListWidget->setItemWidget(item, label);
    }

    void chapterSpaceItem(QListWidgetItem* item)
    {
        QLabel* space = new QLabel(settingsContentListWidget);
        item->setSizeHint(QSize(settingsContentListWidget->width(), 40));
        settingsContentListWidget->setItemWidget(item, space);
    }

    void sectionSpaceItem(QListWidgetItem* item)
    {
        QLabel* space = new QLabel(settingsContentListWidget);
        item->setSizeHint(QSize(settingsContentListWidget->width(), 15));
        settingsContentListWidget->setItemWidget(item, space);
    }
};