#pragma once
#include <QWidget>
#include <QSettings>
#include <QPainter>
#include "ui_Settings.h"
#include "Const.h"

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
    /*~Settings();*/

protected slots:
    void checkIsLineEditNull();
    void deleteSearchText();

private:
    Ui_Settings ui;
    bool searchSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item, QString text);
    void showSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item);
    void notExpandSetting(QTreeWidget* treeWidget);
    void switchOverSearchButton(bool msg);
    void search();

    std::map<QString, QString> settingsCommonMap = {
        {"theme", "Default"},
        {"language", "English"}
    };

    std::map<QString, QString> settingsExportMap = {
        {"defaultSavePath", ""}
    };
};

