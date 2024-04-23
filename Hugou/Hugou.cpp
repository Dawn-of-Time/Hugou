#include "Hugou.h"
#include "Var.h"


extern FloatingNoteManager floatingNoteManager;

Hugou::Hugou(Setting* setting, QWidget* parent)
    : QMainWindow(parent)
{
    // Ui
    ui.setupUi(this);

    pdfEdit = new PDFEdit("C:/Users/Dawn/Desktop/test.pdf");

    // 设置页
    QString settingWidgetStyleSheet = QString(
        "QStackedWidget {margin: 0px; padding: 0px; border-bottom-right-radius: 12px}");
    QString settingLabelStyleSheet = QString(
        "QLabel {margin-left: 20px}");
    QString searchButtonStyleSheet = QString(
        "QPushButton {border: none}");
    QString searchDeletedButtonStyleSheet = QString(
        "QPushButton {border: none}");
    QString settingLeftWidgetStyleSheet = QString(
        ".QWidget {background-color:white; margin: 0px; padding: 0px; border-top: 2px solid #cccccc; border-right: 2px solid #cccccc}");
    QString settingTreeFrameStyleSheet = QString(
        "QFrame {background-color:white; margin: 2px; padding: 0px; border-bottom-right-radius: 12px}");
    QString settingRightWidgetStyleSheet = QString(
        ".QWidget {margin: 0px; padding: 0px; border-top: 2px solid #cccccc; background-color:white; border-bottom-right-radius: 12px}");
    QString settingContentListWidgetStyleSheet = QString(
        "QListWidget {background-color:white; border-bottom-right-radius: 12px; outline: none; margin-left: 20px; margin-right: 12px; margin-top: 2px; margin-bottom: 2px}"
        "QListWidget::item:hover{background-color:none; border-bottom-right-radius: 12px}");
    ui.settingWidget->setStyleSheet(settingWidgetStyleSheet);
    ui.settingLabel->setStyleSheet(settingLabelStyleSheet);
    ui.searchButton->setStyleSheet(searchButtonStyleSheet);
    ui.settingLeftWidget->setStyleSheet(settingLeftWidgetStyleSheet);
    ui.settingTreeFrame->setStyleSheet(settingTreeFrameStyleSheet);
    ui.settingRightWidget->setStyleSheet(settingRightWidgetStyleSheet);
    ui.settingContentListWidget->setStyleSheet(settingContentListWidgetStyleSheet);

    // 设置模糊
    blurEffect = new QGraphicsBlurEffect;
    blurEffect->setBlurRadius(0);
    blurTimer.setInterval(5);
    ui.stackedWidget->setGraphicsEffect(blurEffect);
    // 配置读取和应用
    receiveSetting = setting;
    if (!receiveSetting->readSetting()) // 读取设置并保存到所有settingMap中。一旦有任何错误，立即引发错误提示，并暂时采用默认设定
    {
        raiseReadingSettingError();
        settingCommonMap = defaultCommonMap;
        settingExportMap = defaultExportMap;
    }
    // 实际应用
    //receiveSetting->themeSetting->initTheme(this);
    //receiveSetting->applySetting(this);
    // ui应用
    if (themeList.contains(settingCommonMap["theme"]))
        ui.themeBox->setCurrentIndex(themeList.indexOf(settingCommonMap["theme"]));
    if (languageList.contains(settingCommonMap["language"]))
        ui.languageBox->setCurrentIndex(languageList.indexOf(settingCommonMap["language"]));

    // 信号与槽
    connect(ui.titleBar, &TitleBar::SignalBlurStackedWidget, this, &Hugou::blurStackedWidget);
    connect(ui.titleBar, &TitleBar::SignalClearStackedWidget, this, &Hugou::clearStackedWidget);
    connect(ui.asideBar, &AsideBar::SignalChangeStackedWidget, this, &Hugou::changeStackedWidget);
    connect(ui.searchLineEdit, &QLineEdit::textChanged, this, &Hugou::checkIsLineEditNull);
    connect(ui.searchButton, &QPushButton::clicked, this, &Hugou::search);
    connect(ui.settingTreeWidget, &QTreeWidget::itemClicked, [&](QTreeWidgetItem* item, int column) {item->setExpanded(!item->isExpanded()); });
    connect(ui.settingTreeWidget, &QTreeWidget::itemDoubleClicked, [&](QTreeWidgetItem* item, int column)
        {
            int row = ui.settingItemRowMap[item->text(column)];
            ui.settingContentListWidget->scrollToItem(ui.settingContentListWidget->item(row), QAbstractItemView::PositionAtTop);
        });
    connect(ui.themeBox, &QComboBox::currentIndexChanged, [&](int index)
        {
            QString oldsetting = settingCommonMap["theme"];
            settingCommonMap["theme"] = ui.themeBox->currentText();
            //if (!setting->applySetting(this, "themeBox", oldsetting)) raiseSavingSettingError();
        });
}

Hugou::~Hugou()
{}

void Hugou::changeStackedWidget(int index)
{
    ui.stackedWidget->setCurrentIndex(index);
}

void Hugou::raiseReadingSettingError() { floatingNoteManager.raiseFloatingNote(this, FloatingNote::Type::Error, readingSettingErrorHint);}

void Hugou::raiseSavingSettingError() { floatingNoteManager.raiseFloatingNote(this, FloatingNote::Type::Error, savingSettingErrorHint); }

void Hugou::checkIsLineEditNull()
{
    QString text = ui.searchLineEdit->text().trimmed();
    if (text.length()) switchOverSearchButton(1);
    else switchOverSearchButton(0);
}

// 槽函数
void Hugou::switchOverSearchButton(bool msg)
{
    if (msg)
    {
        ui.searchButton->setIcon(QIcon("res/close_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/close_bla.png"), QString("res/close_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Hugou::deleteSearchText);
        search(); // 一旦有文字输入，总是自动开始寻找匹配项
    }
    else
    {
        ui.searchButton->setIcon(QIcon("res/search_bla.png"));
        ui.searchButtonHoverWatcher->setResource(QString("res/search_bla.png"), QString("res/search_blu.png"));
        ui.searchButton->disconnect();
        connect(ui.searchButton, &QPushButton::clicked, this, &Hugou::search);
        receiveSetting->showSetting(ui.settingTreeWidget, ui.settingTreeWidget->invisibleRootItem()); // 一旦为空，则显示所有项
        ui.settingTreeWidget->setVisible(true);
        ui.searchSettingNullLabel->setVisible(false);
        receiveSetting->notExpandSetting(ui.settingTreeWidget);
    }
}

void Hugou::deleteSearchText()
{
    ui.searchLineEdit->clear();
}

void Hugou::search()
{
    QString searchText = ui.searchLineEdit->text().trimmed();
    receiveSetting->notExpandSetting(ui.settingTreeWidget);
    if (searchText.length())
    {
        int searchNum = receiveSetting->searchSetting(ui.settingTreeWidget, ui.settingTreeWidget->invisibleRootItem(), searchText);
        ui.settingTreeWidget->setVisible(searchNum);
        ui.searchSettingNullLabel->setVisible(!searchNum);
    }
}

void Hugou::openPDFEditFunction()
{
    //FileImportDialog* fileImportDialog = new FileImportDialog(this);
    //fileImportDialog->show();
    //connect(fileImportDialog, &FileImportDialog::uploadSuccessed, [&](QString fileName) 
    //    {
    //        pdfEdit = new PDFEdit(fileName);
    //    });
}

void Hugou::blurStackedWidget()
{
    blurTimer.disconnect();
    connect(&blurTimer, &QTimer::timeout, [&]() 
        {
            if (blurRadius < 60)
            {
                blurRadius += 6;
                blurEffect->setBlurRadius(blurRadius);
            }
            else blurTimer.stop();
        });
    blurTimer.start();
}

void Hugou::clearStackedWidget()
{
    blurTimer.disconnect();
    connect(&blurTimer, &QTimer::timeout, [&]()
        {
            if (blurRadius > 0) {
                blurRadius -= 10;
                blurEffect->setBlurRadius(blurRadius);
            }
            else blurTimer.stop();
        });
    blurTimer.start();
}