#include "Database.h"

Database::Database()
	:QObject()
{
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName("hugou.db");
}

bool Database::open()
{
	if(m_database.open())
		return true;
	else
	{
		QString errorText = m_database.lastError().text();
		dealError(errorText);
		return false;
	}
}

bool Database::exec(QSqlQuery query)
{
	if (query.exec()) return true;
	else
	{
		QString errorText = query.lastError().text();
		dealError(errorText);
		return false;
	}
}

void Database::dealError(QString errorText)
{
	emit SettingsHelper::getHelper()->triggerError("20000", errorText);
}