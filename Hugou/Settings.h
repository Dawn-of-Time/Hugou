#pragma once
#include <QWidget>
#include <QSettings>
#include <QPainter>
#include "ui_Settings.h"
#include "Const.h"
#include "SettingsHelper.h"

const std::map<QString, QString> defaultCommonMap = {
            {"theme", "Default"},
            {"language", "English"} };

const std::map<QString, QString> defaultExportMap = {
    {"defaultSavePath", ""} };

class Settings :
    public QWidget
{
    Q_OBJECT

public:
    Settings(QWidget* parent);
    void adjustSizeHint();
    /*~Settings();*/

signals:
    void SignalApplyTheme(QString theme = "");

protected slots:
    void checkIsLineEditNull();
    void deleteSearchText();

private:
    Ui_Settings ui;
    void showSettings(QTreeWidget* treeWidget, QTreeWidgetItem* item);
    void notExpandSettings(QTreeWidget* treeWidget);
    void switchOverSearchButton(bool msg);
    void searchSettings();
    void showEvent(QShowEvent* event) override;
};

