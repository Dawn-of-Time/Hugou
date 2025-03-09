#include "Utils/Include/Utils_ConfigurationHelper.h"

ConfigurationHelper::ConfigurationHelper()
    : QObject()
{
    verifyAndLoadConfiguration();
}

ConfigurationHelper* ConfigurationHelper::getHelper() 
{
	static ConfigurationHelper helper;
    return &helper;
}

void ConfigurationHelper::verifyAndLoadConfiguration()
{
    if (!verifyConfINIExist()) return;
    QStringList sections = m_confINI.childGroups();
    bool integralityFlag = true;
    bool validityFlag = true;
    for (QMap<QString, QMap<QString, QStringList>>::const_iterator sectionIterator = configurationValidValueMap.begin(); sectionIterator != configurationValidValueMap.end(); sectionIterator++)
    {
        // ������У��֮һ����������У��
        QString section = sectionIterator.key();
        m_confINI.beginGroup(section);
        if (!sections.contains(section))
        {
            integralityFlag = false;
            m_configurationMap[section] = m_defalutValueMap[section];
        }
        else
        {
            QStringList keys = m_confINI.childKeys();  // ��ǰsection�ļ��б�
            for (QMap<QString, QStringList>::const_iterator paramIterator = sectionIterator.value().begin(); paramIterator != sectionIterator.value().end(); paramIterator++)
            {
                // ������У��֮��������������У��
                QString key = paramIterator.key();
                if (!keys.contains(key))
                {
                    integralityFlag = false;
                    m_configurationMap[section].insert(key, m_defalutValueMap[section][key]);
                    continue;
                }
                // �����Ϸ���У��
                QStringList values = configurationValidValueMap[section][key];
                QString value = m_confINI.value(key, "").toString();
                if (values.isEmpty()) // �����ںϷ����б�����У��Ϸ���
                {
                    m_configurationMap[section].insert(key, value);
                    continue;
                }
                if (!values.contains(value))
                {
                    validityFlag = false;
                    m_configurationMap[section].insert(key, m_defalutValueMap[section][key]);
                }
                else m_configurationMap[section].insert(key, value);
            }
        }
        m_confINI.endGroup();
    }
    if (!integralityFlag) emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10001);
    if (!validityFlag) emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10002);
}

// ��ini�����ļ���ȡ
QString ConfigurationHelper::readPreference(const QString& key)
{
    if (!verifyConfINIExist()) return "notExist";
    return m_confINI.value(key, "invalid").toString();
}

// ��ӳ����ȡ
bool ConfigurationHelper::getBasisValue(const QString& key, QString& value)
{
    if (m_configurationMap["Basis"].contains(key))
    {
        value = m_configurationMap["Basis"][key];
        return true;
    }
    else
        return false;
}

bool ConfigurationHelper::getPreferenceValue(const QString& key, QString& value)
{
    if (m_configurationMap["Preference"].contains(key))
    {
        value = m_configurationMap["Preference"][key];
        return true;
    }
    else
        return false;
}

bool ConfigurationHelper::getRecordValue(const QString& key, QString& value)
{
    if (m_configurationMap["Record"].contains(key))
    {
        value = m_configurationMap["Record"][key];
        return true;
    }
    else
        return false;
}

// д��ӳ���
void ConfigurationHelper::setBasisValue(const QString& key, const QString& value)
{
    m_configurationMap["Basis"][key] = value;
    if (writeConfiguration("Basis", key, value)) m_isChanged = true;
}

void ConfigurationHelper::setPreferenceValue(const QString& key, const QString& value)
{
    m_configurationMap["Preference"][key] = value;
    if (writeConfiguration("Preference", key, value)) m_isChanged = true;
}

void ConfigurationHelper::setRecordValue(const QString& key, const QString& value)
{
    m_configurationMap["Record"][key] = value;
    if (writeConfiguration("Record", key, value)) m_isChanged = true;
}

bool ConfigurationHelper::writeConfiguration(const QString& section, const QString& key, const QString& value)
{
    if (!verifyConfINIExist()) return false;
    m_confINI.beginGroup(section);
    m_confINI.setValue(key, value);
    m_confINI.endGroup();
    return true;
}

void ConfigurationHelper::syncConfiguration()
{
    if (m_isChanged)
    {
        if (!verifyConfINIExist()) return;
        m_confINI.sync();
    }
}

bool ConfigurationHelper::verifyConfINIExist()
{
    if (!QFile("Configuration/conf.ini").exists())
    {
        emit MessegeHelper::getHelper()->trigger(FloatingNote::Error, 10000);
        return false;
    }
    return true;
}