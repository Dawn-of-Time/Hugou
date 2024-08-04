#include "SettingsHelper.h"

SettingsHelper::SettingsHelper(QWidget* Hugou)
    : QObject()
{
    this->Hugou = Hugou;
    connect(this, &SettingsHelper::triggerError, this, &SettingsHelper::dealError);
}

bool SettingsHelper::verifySettings()
{
    if (!verifyConfINIExist()) return false;
    QSettings confINI(":/Hugou/res/conf.ini", QSettings::IniFormat);
    QStringList confINIList = confINI.allKeys();
    for (const QString& key : settingsKeyList)
    {
        if (!confINI.allKeys().contains(key))
        {
            emit triggerError(10001);
            return false;
        }
    }
    for(const QString& key : settingsKeyList) {
        if (settingValueMap.find(key) != settingValueMap.end())
        {
            QStringList value = settingValueMap.find(key)->second;
            if (!value.contains((confINI.value(key, "invalid").toString())))
            {
                emit triggerError(10002);
                return false;
            }
        }
    }
    return true;
}

QString SettingsHelper::readSettings(QString key)
{
    if (!verifyConfINIExist()) return "notExist";
    QSettings confINI(":/Hugou/res/conf.ini", QSettings::IniFormat);
    return confINI.value(key, "invalid").toString();
}

bool SettingsHelper::writeSettings(QString key, QString value)
{
    if (!verifyConfINIExist()) return false;
    QSettings confINI("res/conf.ini", QSettings::IniFormat);
    confINI.setValue(key, value);
    return true;
}

void SettingsHelper::syncSettings()
{
    if (!verifyConfINIExist()) return;
    QSettings confINI("res/conf.ini", QSettings::IniFormat);
    confINI.sync();
}

// ²Ûº¯Êý
void SettingsHelper::dealError(int errorCode)
{
    QSettings errorCodeINI(":/Hugou/res/errorCode.ini", QSettings::IniFormat);
    QSettings solutionINI(":/Hugou/res/solution.ini", QSettings::IniFormat);
    QString content = errorCodeINI.value(QString::number(errorCode), "Unknown error code.").toString() + "(Error Code: " + QString::number(errorCode) + ")";
    QString subcontent = solutionINI.value(QString::number(errorCode), "No solution found.").toString();
    floatingNoteManager.raiseFloatingNote(Hugou, FloatingNote::Error, content, subcontent);
}

bool SettingsHelper::verifyConfINIExist()
{
    if (!QFile(":/Hugou/res/conf.ini").exists())
    {
        emit triggerError(10000);
        return false;
    }
    return true;
}

//bool SettingsHelper::verifyConfINIInvalid()
//{
//    if (!QFile("conf.ini").exists())
//    {
//        emit triggerError(1000);
//        return false;
//    }
//    QStringList value = settingValueMap.find(key)->second;
//    if (!value.contains((confINI.value(key, "invalid").toString())))
//    {
//        emit triggerError(1002);
//        return false;
//    }
//    return true;
//}