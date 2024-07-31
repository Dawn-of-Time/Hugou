#include "Setting.h"

Setting::Setting()
{}

Setting::~Setting()
{}

// TODO: 1.只有完全读取之后才真正应用
//bool Setting::readSetting()
//{
//    QSettings iniSettings("conf.ini", QSettings::IniFormat);
//    QStringList readSettingGroupList = iniSettings.childGroups();
//    if (readSettingGroupList != settingGroupList) return false;
//    foreach(QString group, settingGroupList) {
//        iniSettings.beginGroup(group);
//        if (group == "Common") {
//            for (auto itr = settingCommonMap.begin(); itr != settingCommonMap.end(); ++itr) {
//                QString key = itr->first;
//                if (iniSettings.contains(key)) settingCommonMap[key] = QString(iniSettings.value(key).toString());
//                else return false;
//            }
//        }
//        if (group == "Export") {
//            for (auto itr = settingExportMap.begin(); itr != settingExportMap.end(); ++itr) {
//                QString key = itr->first;
//                if (iniSettings.contains(key)) settingExportMap[key] = QString(iniSettings.value(key).toString());
//                else return false;
//            }
//        }
//        iniSettings.endGroup();
//    }
//    return true;
//}

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
