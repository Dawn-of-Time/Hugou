#include "Setting.h"

std::map<QString, QString> settingCommonMap = {
{"theme", "Default"},
{"language", "English"}
};

std::map<QString, QString> settingExportMap = {
    {"defaultSavePath", ""}
};

Setting::Setting()
{}

Setting::~Setting()
{}

bool Setting::searchSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item, QString text)
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

void Setting::showSetting(QTreeWidget* treeWidget, QTreeWidgetItem* item)
{
    item->setHidden(false);
    for (int i = 0; i < item->childCount(); ++i)
    {
        QTreeWidgetItem* child = item->child(i);
        showSetting(treeWidget, child);
    }
}

void Setting::notExpandSetting(QTreeWidget* treeWidget)
{
    for (int i = 0; i < treeWidget->invisibleRootItem()->childCount(); ++i)
    {
        treeWidget->invisibleRootItem()->child(i)->setExpanded(false);
    }
}

// TODO: 1.只有完全读取之后才真正应用
bool Setting::readSetting()
{
    QSettings iniSettings("conf.ini", QSettings::IniFormat);
    QStringList readSettingGroupList = iniSettings.childGroups();
    if (readSettingGroupList != settingGroupList) return false;
    foreach(QString group, settingGroupList) {
        iniSettings.beginGroup(group);
        if (group == "Common") {
            for (auto itr = settingCommonMap.begin(); itr != settingCommonMap.end(); ++itr) {
                QString key = itr->first;
                if (iniSettings.contains(key)) settingCommonMap[key] = QString(iniSettings.value(key).toString());
                else return false;
            }
        }
        if (group == "Export") {
            for (auto itr = settingExportMap.begin(); itr != settingExportMap.end(); ++itr) {
                QString key = itr->first;
                if (iniSettings.contains(key)) settingExportMap[key] = QString(iniSettings.value(key).toString());
                else return false;
            }
        }
        iniSettings.endGroup();
    }
    return true;
}

//bool Setting::applySetting(Hugou* HugouClass, QString objectName, QString oldsetting)
//{
//    if (objectName == "themeBox")
//    {
//        settingCommonMap["theme"] = HugouClass->ui.themeBox->currentText();
//        this->themeSetting->setTheme(HugouClass, settingCommonMap["theme"]);
//    }
//    else // 这种情况下，所有配置都被应用
//    {
//        this->themeSetting->setTheme(HugouClass, settingCommonMap["theme"]);
//        return true;
//    }
//    return saveSetting(HugouClass, objectName, oldsetting);
//}
//
//bool Setting::saveSetting(Hugou* HugouClass, QString objectName, QString oldsetting)
//{
//    QSettings iniSettings("conf.ini", QSettings::IniFormat);
//    QStringList readSettingKeyList = iniSettings.allKeys();
//    bool undoFlag = false;
//    if (objectName == "themeBox")
//    {
//        if (!readSettingKeyList.contains("Common/theme")) undoFlag = true;
//        if (undoFlag)
//        {
//            undoSetting(HugouClass, objectName, oldsetting); // 一旦保存不成功，撤回修改
//            return false;
//        }
//        else iniSettings.setValue("Common/theme", settingCommonMap["theme"]);
//    }
//    return true;
//}
//
//void Setting::undoSetting(Hugou* HugouClass, QString objectName, QString oldsetting)
//{
//    if (objectName == "themeBox")
//    {
//        settingCommonMap["theme"] = oldsetting;  // 撤回修改
//        HugouClass->ui.themeBox->setCurrentIndex(themeList.indexOf(oldsetting));
//    }
//}

void Setting::resetSetting()
{

}

void Setting::resetAllSetting()
{

}
