#include "Assistance/Include/Assistance_PreferenceHelper.h"

PreferenceHelper::PreferenceHelper()
    : QObject()
{
    verifyAndLoadpreference();
}

PreferenceHelper* PreferenceHelper::getHelper() 
{
	static PreferenceHelper helper;
    return &helper;
}

void PreferenceHelper::verifyAndLoadpreference()
{
    if (!verifyConfINIExist()) return;
    QStringList confINIList = m_confINI.allKeys();
    bool integralityFlag = true;
    bool validityFlag = true;
    for (const QString& key : preferenceKeyList)
    {
        // ������������У��
        if (!confINIList.contains(key))
        {
            integralityFlag = false;
            m_preferenceMap.insert(key, defalutPreferenceValueMap[key]);
            continue;
        }
        // ������Ϸ���У��
        QStringList values = preferenceValueMap[key];
        QString value = m_confINI.value(key, "").toString();
        if (values.isEmpty()) // ����У��Ϸ���
        {
            m_preferenceMap.insert(key, value);
            continue;
        }
        if (!values.contains(value))
        {
            validityFlag = false;
            m_preferenceMap.insert(key, defalutPreferenceValueMap[key]);
        }
        else m_preferenceMap.insert(key, value);
    }

    if (!integralityFlag) emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10001);
    if (!validityFlag) emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10002);
}

// ��ini�����ļ���ȡ
QString PreferenceHelper::readpreference(const QString& key)
{
    if (!verifyConfINIExist()) return "notExist";
    return m_confINI.value(key, "invalid").toString();
}

// ��ӳ����ȡ
bool PreferenceHelper::getPreferenceValue(const QString& key, QString& value)
{
    if (m_preferenceMap.contains(key))
    {
        value = m_preferenceMap[key];
        return true;
    }
    else
        return false;
}

// д��ӳ���
void PreferenceHelper::setPreferenceValue(const QString& key, const QString& value)
{
    m_preferenceMap[key] = value;
    if (writePreference(key, value)) m_isChanged = true;
}

bool PreferenceHelper::writePreference(const QString& key, const QString& value)
{
    if (!verifyConfINIExist()) return false;
    m_confINI.setValue(key, value);
    return true;
}

void PreferenceHelper::syncPreference()
{
    if (m_isChanged)
    {
        if (!verifyConfINIExist()) return;
        m_confINI.sync();
    }
}

bool PreferenceHelper::verifyConfINIExist()
{
    if (!QFile("Configuration/conf.ini").exists())
    {
        emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10000);
        return false;
    }
    return true;
}