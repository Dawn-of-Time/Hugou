﻿#pragma once

#include <QtCore/QVariant>
#include <QApplication>
#include <QtWidgets>
#include <QFont>
#include "TitleBar.h"
#include "AsideBar.h"
#include "Const.h"
#include "ButtonHoverWatcher.h"
#include "ComboboxWheelWatcher.h"
#include "WorkSpace.h"

QT_BEGIN_NAMESPACE

class Ui_HugouClass
{
public:
    QHBoxLayout* generalBackgroundLayout;
    QWidget* generalBackground;
    QHBoxLayout* generalLayout;
    QWidget* titleBarAndStackedWidget;
    QVBoxLayout* titleBarAndStackedLayout;
    TitleBar* titleBar;
    AsideBar* asideBar;
    QStackedWidget* stackedWidget;
    WorkSpace* workSpaceWidget;
    QWidget* settingWidget;
    QLabel* settingLabel;
    QVBoxLayout* settingWidgetLayout;
    QWidget* settingLeftWidget;
    QVBoxLayout* settingLeftLayout;
    QLineEdit* searchLineEdit;
    QPushButton* searchButton;
    QPushButton* searchDeletedButton;
    ButtonHoverWatcher* searchButtonHoverWatcher;
    ButtonHoverWatcher* searchDeletedButtonHoverWatcher;
    QFrame* settingTreeFrame;
    QVBoxLayout* settingTreeLayout;
    QTreeWidget* settingTreeWidget;
    QLabel* searchSettingNullLabel;
    QWidget* settingRightWidget;
    QListWidget* settingContentListWidget;
    QComboBox* themeBox;
    QComboBox* languageBox;
    QPushButton* savePathButton;
    QLineEdit* savePathLineEdit;
    std::map<QString, int> settingItemRowMap;

    void setupUi(QWidget* HugouClass)
    {
        // 1 主窗口
        // --基本属性设置
        HugouClass->setObjectName("HugouClass");
        HugouClass->setMinimumSize(mainWindowWidth, mainWindowHeight);

        // --无边框窗口
        // 注：使用无边框窗口的一个目标是方便自定义标题栏。事实上，使用Qt::CustomizeWindowHint标志会更方便一些，
        //    因为Qt::FramelessWindowHint标志将会一并移出窗口边缘的拉伸效果，同时并不自带圆角效果。遗憾的是，
        //    使用Qt::CustomizeWindowHint标志后，会在窗口的顶端残留白条，并不美观。因此考虑使用
        //    Qt::FramelessWindowHint标志，其余功能自行实现。
        HugouClass->setWindowFlags(Qt::FramelessWindowHint);

        // --透明背景
        HugouClass->setAttribute(Qt::WA_TranslucentBackground);


        // 2 主布局
        // 注：由于期望将主窗口设置圆角，而在Qt中无法将无父控件的控件通过设置qss的border-radius属性来改变圆角。
        //    这里将主窗口设置为透明背景，然后叠加一层控件作为主背景。
        // --主背景
        // 注：之后的控件在主背景上产生。主背景的四周存在间隙，用于实现拖拽以变更窗口大小的功能。
        generalBackgroundLayout = new QHBoxLayout(HugouClass);
        generalBackgroundLayout->setSpacing(0);
        generalBackgroundLayout->setContentsMargins(0, 0, 0, 0);

        generalBackground = new QWidget(HugouClass);
        generalBackground->setObjectName("generalBackground");

        generalBackgroundLayout->addWidget(generalBackground);

        // --主布局
        generalLayout = new QHBoxLayout(generalBackground);
        generalLayout->setSpacing(0);
        generalLayout->setContentsMargins(10, 10, 10, 10);
        // ----侧边栏
        asideBar = new AsideBar(generalBackground);
        // ----标题栏与堆叠控件
        titleBarAndStackedWidget = new QWidget(generalBackground);
        titleBarAndStackedLayout = new QVBoxLayout(titleBarAndStackedWidget);
        titleBarAndStackedLayout->setSpacing(0);
        titleBarAndStackedLayout->setContentsMargins(0, 0, 0, 0);
        // ------标题栏
        titleBar = new TitleBar(titleBarAndStackedWidget);
        // ------堆叠控件
        stackedWidget = new QStackedWidget(titleBarAndStackedWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(0, titleFrameHeight, stackedWidgetWidth, stackedWidgetHeight);
        // --------堆叠控件：WorkSpace
        workSpaceWidget = new WorkSpace(stackedWidget);
        // --------堆叠控件：Setting
        settingWidget = new QWidget(stackedWidget);
        settingWidget->setObjectName("settingWidget");
        settingLabel = new QLabel("Settings", settingWidget); // 界面标题板块
        settingLabel->setObjectName("settingLabel");
        settingLabel->setFixedHeight(stackedTitleHeight);
        settingLabel->setFont(QFont("Hind", 40));
        // 左栏
        settingLeftWidget = new QWidget(settingWidget);
        settingLeftWidget->setObjectName("settingLeftWidget");
        settingLeftWidget->setGeometry(0, stackedTitleHeight + 10, settingWidget->width() / 4, stackedWidgetHeight - stackedTitleHeight - 10);
        settingLeftLayout = new QVBoxLayout(settingLeftWidget);
        settingLeftLayout->setObjectName("settingLeftLayout");

        // 搜索区域
        searchLineEdit = new QLineEdit(settingLeftWidget);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setFixedWidth(settingLeftWidget->width());
        searchLineEdit->setPlaceholderText(searchText);
        searchLineEdit->setFont(QFont("Hind Siliguri", 13));
        QPalette searchPalette = searchLineEdit->palette();
        searchPalette.setColor(searchPalette.PlaceholderText, QColor("#cccccc"));
        searchButton = new QPushButton(searchLineEdit);
        searchButton->setObjectName("searchButton");
        searchButton->setIcon(QIcon("res/search_bla.png"));
        searchButton->setCursor(Qt::ArrowCursor);
        QWidgetAction* searchAction = new QWidgetAction(searchLineEdit);
        searchAction->setDefaultWidget(searchButton);
        searchLineEdit->addAction(searchAction, QLineEdit::TrailingPosition);
        searchButtonHoverWatcher = new ButtonHoverWatcher(QString("res/search_bla.png"), QString("res/search_blu.png"), HugouClass);
        searchButton->installEventFilter(searchButtonHoverWatcher);

        // 目录
        settingTreeFrame = new QFrame(HugouClass);
        settingTreeFrame->setFixedSize(settingLeftWidget->width(), settingLeftWidget->height() - searchLineEdit->height());
        settingTreeWidget = new QTreeWidget(HugouClass);
        settingTreeWidget->setHeaderHidden(true);
        settingTreeWidget = formTree(settingTreeWidget);
        settingTreeWidget->setFont(QFont("Hind Siliguri", 13));
        searchSettingNullLabel = new QLabel("No matches were found.", HugouClass);
        searchSettingNullLabel->setVisible(false); // 默认不显示“未找到匹配项”
        searchSettingNullLabel->setFont(QFont("Hind Siliguri", 13));
        searchSettingNullLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        settingTreeLayout = new QVBoxLayout(settingTreeFrame);
        settingTreeLayout->setContentsMargins(0, 0, 0, 0);
        settingTreeLayout->addWidget(settingTreeWidget);
        settingTreeLayout->addWidget(searchSettingNullLabel);
        settingLeftLayout->addWidget(searchLineEdit, 1);
        settingLeftLayout->addWidget(settingTreeFrame, 9);
        settingLeftLayout->setContentsMargins(0, 0, 0, 0);

        // 右栏
        settingRightWidget = new QWidget(settingWidget);
        settingRightWidget->setObjectName("settingLeftWidget");
        settingRightWidget->setGeometry(settingLeftWidget->width(), settingLeftWidget->y(), settingWidget->width() - settingLeftWidget->width(), settingLeftWidget->height());
        settingContentListWidget = new QListWidget(settingRightWidget);
        settingContentListWidget = formContentList(settingContentListWidget);
        settingContentListWidget->setSelectionRectVisible(false);
        settingContentListWidget->setFixedSize(settingRightWidget->width(), settingRightWidget->height());

        stackedWidget->addWidget(workSpaceWidget);
        stackedWidget->addWidget(settingWidget);
        stackedWidget->setCurrentWidget(workSpaceWidget);

        titleBarAndStackedLayout->addWidget(titleBar);
        titleBarAndStackedLayout->addWidget(stackedWidget);

        generalLayout->addWidget(asideBar);
        generalLayout->addWidget(titleBarAndStackedWidget);

        QFile styleFile("res/style/Default/general.qss");
        styleFile.open(QIODeviceBase::ReadOnly);
        HugouClass->setStyleSheet(styleFile.readAll());
        styleFile.close();

        retranslateUi(HugouClass);
    } // setupUi

    QTreeWidget* formTree(QTreeWidget* settingTreeWidget)
    {
        // 一级目录
        QTreeWidgetItem* item1 = new QTreeWidgetItem(settingTreeWidget);
        item1->setText(0, "Common");
        item1->setIcon(0, QIcon("res/common.png"));
        settingTreeWidget->addTopLevelItem(item1);
        QTreeWidgetItem* item2 = new QTreeWidgetItem(settingTreeWidget);
        item2->setText(0, "Export");
        item2->setIcon(0, QIcon("res/export.png"));
        settingTreeWidget->addTopLevelItem(item2);

        // 二级目录
        QTreeWidgetItem* item1_1 = new QTreeWidgetItem(item1);
        item1_1->setText(0, "Appearance");
        item1_1->setIcon(0, QIcon("res/appearance.png"));
        QTreeWidgetItem* item1_2 = new QTreeWidgetItem(item1);
        item1_2->setText(0, "Country/Region");
        item1_2->setIcon(0, QIcon("res/country_region.png"));

        return settingTreeWidget;
    }

    void firstNodeSettingItem(QListWidgetItem* item, QString settingName)
    {
        QString firstNodeStyleSheet = "QLabel {border-width: 0 0 0 5px; border-style: solid; border-color: black; padding-left: 2px}";
        QSize firstNodeSizeHint = QSize(settingContentListWidget->width(), 40);
        QFont firstNodeFont = QFont("Hind Siliguri", 22);
        QLabel* label = new QLabel(settingContentListWidget);
        label->setText(settingName);
        label->setFont(firstNodeFont);
        label->setStyleSheet(firstNodeStyleSheet);
        item->setSizeHint(firstNodeSizeHint);
        settingContentListWidget->setItemWidget(item, label);
        settingItemRowMap.insert({ settingName, settingContentListWidget->indexFromItem(item).row() });
    }

    void secondNodeSettingItem(QListWidgetItem* item, QString settingName)
    {
        QString secondNodeStyleSheet = "QLabel {margin-left: 15px}";
        QFont secondNodeFont = QFont("Hind Siliguri", 16);
        QLabel* label = new QLabel(settingContentListWidget);
        label->setText(settingName);
        label->setFont(secondNodeFont);
        label->setStyleSheet(secondNodeStyleSheet);
        label->setAlignment(Qt::AlignBottom);
        item->setSizeHint(QSize(settingContentListWidget->width(), 40));
        settingContentListWidget->setItemWidget(item, label);
        settingItemRowMap.insert({ settingName, settingContentListWidget->indexFromItem(item).row() });
    }

    void thirdNodeSettingItem(QListWidgetItem* item, QString settingName)
    {
        QString thirdNodeStyleSheet = "QLabel {margin-left: 20px}";
        QFont thirdNodeFont = QFont("Hind Siliguri Light", 14);
        QLabel* label = new QLabel(settingContentListWidget);
        label->setText(settingName);
        label->setFont(thirdNodeFont);
        label->setStyleSheet(thirdNodeStyleSheet);
        label->setAlignment(Qt::AlignBottom);
        item->setSizeHint(QSize(settingContentListWidget->width(), 30));
        settingContentListWidget->setItemWidget(item, label);
        settingItemRowMap.insert({ settingName, settingContentListWidget->indexFromItem(item).row() });
    }

    QComboBox* contentNodeComboboxSettingItem(QListWidgetItem* item, QString objectName, QStringList comboboxList)
    {
        QString contentStyleSheet = "QLabel {margin-left: 20px}";
        QString contentComboBoxStyleSheet = ".QComboBox {margin-left: 15px}";
        QFont contentFont = QFont("Hind Siliguri Light", 12);
        QLabel* label = new QLabel(settingContentListWidget);
        label->setStyleSheet(contentStyleSheet);
        QComboBox* comboBox = new QComboBox(label);
        comboBox->setObjectName(objectName);
        comboBox->move(20, 0);
        comboBox->addItems(comboboxList);
        comboBox->setFont(contentFont);
        comboBox->setFixedSize(200, 30);
        ComboboxWheelWatcher* comboBoxWheelWatcher = new ComboboxWheelWatcher(item->listWidget());
        comboBox->installEventFilter(comboBoxWheelWatcher);
        item->setSizeHint(QSize(settingContentListWidget->width(), 30));
        settingContentListWidget->setItemWidget(item, label);
        return comboBox;
    }

    QLineEdit* contentNodeLineEditSettingItem(QListWidgetItem* item)
    {
        QString contentStyleSheet = "QLabel {margin-left: 20px}";
        QString contentLineEditStyleSheet = ".QLineEdit {margin-left: 15px; border: none }";
        QFont contentFont = QFont("Hind Siliguri Light", 12);
        QLabel* label = new QLabel(settingContentListWidget);
        label->setStyleSheet(contentStyleSheet);
        QLineEdit* lineEdit = new QLineEdit(label);
        lineEdit->move(20, 0);
        lineEdit->setFont(contentFont);
        lineEdit->setFixedSize(400, 30);
        item->setSizeHint(QSize(settingContentListWidget->width(), 30));
        settingContentListWidget->setItemWidget(item, label);
        return lineEdit;
    }

    void hintSettingItem(QListWidgetItem* item, QString hint)
    {
        QString hintStyleSheet = "QLabel {margin-left: 20px; color: #696969}";
        QFont hintFont = QFont("Hind Siliguri Light", 12);
        QLabel* label = new QLabel(settingContentListWidget);
        label->setFixedWidth(600);
        label->setFont(hintFont);
        label->setStyleSheet(hintStyleSheet);
        label->setWordWrap(true);
        label->setText(hint);
        label->adjustSize();
        item->setSizeHint(QSize(600, label->height()));
        settingContentListWidget->setItemWidget(item, label);
    }

    void chapterSpaceItem(QListWidgetItem* item)
    {
        QLabel* space = new QLabel(settingContentListWidget);
        item->setSizeHint(QSize(settingContentListWidget->width(), 40));
        settingContentListWidget->setItemWidget(item, space);
    }

    void sectionSpaceItem(QListWidgetItem* item)
    {
        QLabel* space = new QLabel(settingContentListWidget);
        item->setSizeHint(QSize(settingContentListWidget->width(), 15));
        settingContentListWidget->setItemWidget(item, space);
    }

    QListWidget* formContentList(QListWidget* settingContentListWidget)
    {
        // HeadSpace
        QListWidgetItem* headSpaceItem = new QListWidgetItem(settingContentListWidget);
        QLabel* headSpace = new QLabel(settingContentListWidget);
        headSpaceItem->setSizeHint(QSize(settingContentListWidget->width(), 10));
        settingContentListWidget->setItemWidget(headSpaceItem, headSpace);

        // 1-General
        QListWidgetItem* item1 = new QListWidgetItem(settingContentListWidget);
        firstNodeSettingItem(item1, "Common");
        // 1.1-Appearance
        QListWidgetItem* item1_1 = new QListWidgetItem(settingContentListWidget);
        secondNodeSettingItem(item1_1, "Appearance");
        // 1.1.1-Theme
        QListWidgetItem* item1_1_1 = new QListWidgetItem(settingContentListWidget);
        thirdNodeSettingItem(item1_1_1, "Theme");
        // Theme Hint
        QListWidgetItem* hint1 = new QListWidgetItem(settingContentListWidget);
        hintSettingItem(hint1, "I will be launching the theme preview feature in the near future.");
        // 1.1.1.1-themeBox
        QListWidgetItem* item1_1_1_1 = new QListWidgetItem(settingContentListWidget);
        themeBox = contentNodeComboboxSettingItem(item1_1_1_1, "themeBox", themeList);
        // Space1
        QListWidgetItem* spaceItem1 = new QListWidgetItem(settingContentListWidget);
        sectionSpaceItem(spaceItem1);
        // 1.2-Country/Region
        QListWidgetItem* item1_2 = new QListWidgetItem(settingContentListWidget);
        secondNodeSettingItem(item1_2, "Country/Region");
        // 1.2.1-Language
        QListWidgetItem* item1_2_1 = new QListWidgetItem(settingContentListWidget);
        thirdNodeSettingItem(item1_2_1, "Language");
        // Language Hint
        QListWidgetItem* hint2 = new QListWidgetItem(settingContentListWidget);
        hintSettingItem(hint2, "More and more languages are getting support. The language currently in the pipeline is: Chinese.");
        // 1.2.1.1-languageBox
        QListWidgetItem* item1_2_1_1 = new QListWidgetItem(settingContentListWidget);
        languageBox = contentNodeComboboxSettingItem(item1_2_1_1, "languageBox", languageList);
        // Space2
        QListWidgetItem* spaceItem2 = new QListWidgetItem(settingContentListWidget);
        chapterSpaceItem(spaceItem2);

        // 2-Export
        QListWidgetItem* item2 = new QListWidgetItem(settingContentListWidget);
        firstNodeSettingItem(item2, "Export");
        // 2.1-Save
        QListWidgetItem* item2_1 = new QListWidgetItem(settingContentListWidget);
        secondNodeSettingItem(item2_1, "Save");
        // 2.1.1-Default Save Path
        QListWidgetItem* item2_1_1 = new QListWidgetItem(settingContentListWidget);
        thirdNodeSettingItem(item2_1_1, "Default Save Path");
        // Save Path Hint
        QListWidgetItem* hint3 = new QListWidgetItem(settingContentListWidget);
        hintSettingItem(hint3, "This feature is to be developed.");
        // 2.1.1.1-save path lineedit
        QListWidgetItem* item2_1_1_1 = new QListWidgetItem(settingContentListWidget);
        savePathLineEdit = contentNodeLineEditSettingItem(item2_1_1_1);
        savePathButton = new QPushButton(savePathLineEdit);
        savePathButton->setObjectName("savePathButton");
        savePathButton->setIcon(QIcon("res/browse_bla.png"));
        savePathButton->setCursor(Qt::ArrowCursor);
        QWidgetAction* savePathAction = new QWidgetAction(savePathLineEdit);
        savePathAction->setDefaultWidget(savePathButton);
        savePathLineEdit->addAction(savePathAction, QLineEdit::TrailingPosition);
        ButtonHoverWatcher* savePathButtonHoverWatcher = new ButtonHoverWatcher(QString("res/browse_bla.png"), QString("res/browse_blu.png"));
        savePathButton->installEventFilter(savePathButtonHoverWatcher);

        // TailSpace
        QListWidgetItem* tailSpaceItem = new QListWidgetItem(settingContentListWidget);
        QLabel* tailSpace = new QLabel(settingContentListWidget);
        headSpaceItem->setSizeHint(QSize(settingContentListWidget->width(), 15));
        settingContentListWidget->setItemWidget(tailSpaceItem, tailSpace);

        // 不可选定
        for (int i = 0; i < settingContentListWidget->count(); ++i)
        {
            QListWidgetItem* item = settingContentListWidget->item(i);
            item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        }
        return settingContentListWidget;
    }


    void retranslateUi(QWidget* HugouClass)
    {
        HugouClass->setWindowTitle(QCoreApplication::translate("HugouClass", "Hugou", nullptr));
    } 
};

QT_END_NAMESPACE
