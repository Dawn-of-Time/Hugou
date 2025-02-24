#include "Database.h"

Database::Database()
	:QObject()
{
	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName("hugou.db");
	open();
	// 创建数据表
	QStringList tableList = {};
	QSqlQuery query;
	query.exec("SELECT name FROM sqlite_master WHERE type='table'");
	while (query.next())
		tableList.append(query.value(0).toString());
	if (!tableList.contains("memotype_label")) createMemoTypeLabelDatabase();
	if (!tableList.contains("memotype")) createMemoTypeDatabase();
	if (!tableList.contains("memo")) createMemoDatabase();
	if (!tableList.contains("award")) createAwardDatabase();
	if (!tableList.contains("reference")) createReferenceDatabase();
	if (!tableList.contains("memo_award")) createMemoAndAwardDatabase();
	if (!tableList.contains("memo_reference")) createMemoAndReferenceDatabase();
	if (!tableList.contains("memo_submemo")) createMemoAndSubMemoDatabase();
}

void Database::createMemoDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memo("
		"ID                   INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Sketch               VARCHAR(255) NOT NULL, "
		"Template             VARCHAR(255) NOT NULL, "
		"Type                 INTEGER      NOT NULL, "
		"Status               BIT      DEFAULT 0, "
		"PostponeFlag         BIT      DEFAULT 0, "
		"TimePeriod_F         DATETIME DEFAULT NULL, "
		"TimePeriod_L         DATETIME DEFAULT NULL, "
		"TimePoint            DATETIME DEFAULT NULL, "
		"ImportanceAndUrgency TINYINT  DEFAULT 0, "
		"Detail               TEXT     DEFAULT NULL, "
		"RetentionPeriod      TINYINT  DEFAULT -1, "
		"HasSubMemo           BIT      DEFAULT 0, "
		"HasAward             BIT      DEFAULT 0, "
		"HasReference         BIT      DEFAULT 0, "
		"FOREIGN KEY(Type) REFERENCES type(ID)"
		");"
	);
	exec(creatQuery);
}

void Database::createMemoTypeLabelDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memotype_label("
		"ID     INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Name   VARCHAR(255) NOT NULL "
		");"
	);
	exec(creatQuery);

	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO memotype_label(Name) VALUES(:Name1), (:Name2), (:Name3);"
	);
	insertQuery.bindValue(":Name1", "Work");
	insertQuery.bindValue(":Name2", "Learn");
	insertQuery.bindValue(":Name3", "Recreation");
	exec(insertQuery);
}

void Database::createMemoTypeDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memotype("
		"ID       INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Name     VARCHAR(255) NOT NULL, "
		"Color    VARCHAR(7)   NOT NULL, "
		"Label    INTEGER      NOT NULL, "
		"Priority TINYINT      DEFAULT 0, "
		"FOREIGN KEY(Label) REFERENCES memotype_label(ID)"
		");"
	);
	exec(creatQuery);

	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO memotype(Name, Color, Label, Priority) VALUES(:Name1, :Color1, :Label1, :Priority1), (:Name2, :Color2, :Label2, :Priority2), (:Name3, :Color3, :Label3, :Priority3);"
	);
	insertQuery.bindValue(":Name1", "Chinese");
	insertQuery.bindValue(":Color1", "#f85f73");
	insertQuery.bindValue(":Label1", 1);
	insertQuery.bindValue(":Priority1", 1);
	insertQuery.bindValue(":Name2", "Math");
	insertQuery.bindValue(":Color2", "#5b89d8");
	insertQuery.bindValue(":Label2", 1);
	insertQuery.bindValue(":Priority2", 2);
	insertQuery.bindValue(":Name3", "English");
	insertQuery.bindValue(":Color3", "#24b4a5");
	insertQuery.bindValue(":Label3", 1);
	insertQuery.bindValue(":Priority3", 3);
	exec(insertQuery);
}

void Database::createAwardDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS award("
		"ID              INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Sketch          VARCHAR(255) NOT NULL, "
		"Status          BIT      DEFAULT 0, "
		"TimePeriod_F    DATETIME DEFAULT NULL, "
		"TimePeriod_L    DATETIME DEFAULT NULL, "
		"TimePoint       DATETIME DEFAULT NULL, "
		"Detail          TEXT     DEFAULT NULL, "
		"RetentionPeriod TINYINT  DEFAULT -1 "
		");"
	);
	exec(creatQuery);
}

void Database::createReferenceDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS reference("
		"ID              INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Sketch          VARCHAR(255) NOT NULL, "
		"Type            TINYINT      NOT NULL, "
		"Link            TEXT         NOT NULL, "
		"RetentionPeriod TINYINT  DEFAULT -1 "
		");"
	);
	exec(creatQuery);
}

void Database::createMemoAndAwardDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memo_award("
		"MemoID     INTEGER  NOT NULL, "
		"AwardID    INTEGER  NOT NULL, "
		"PRIMARY KEY(MemoID, AwardID),"
		"FOREIGN KEY(MemoID) REFERENCES memo(ID),"
		"FOREIGN KEY(AwardID) REFERENCES award(ID)"
		");"
	);
	exec(creatQuery);
}

void Database::createMemoAndReferenceDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memo_reference("
		"MemoID         INTEGER  NOT NULL, "
		"ReferenceID    INTEGER  NOT NULL, "
		"PRIMARY KEY(MemoID, ReferenceID),"
		"FOREIGN KEY(MemoID) REFERENCES memo(ID),"
		"FOREIGN KEY(ReferenceID) REFERENCES reference(ID)"
		");"
	);
	exec(creatQuery);
}

void Database::createMemoAndSubMemoDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memo_submemo("
		"MemoID       INTEGER  NOT NULL, "
		"SubMemoID    INTEGER  NOT NULL, "
		"PRIMARY KEY(MemoID, SubMemoID),"
		"FOREIGN KEY(MemoID) REFERENCES memo(ID),"
		"FOREIGN KEY(SubMemoID) REFERENCES memo(ID)"
		");"
	);
	exec(creatQuery);
}

bool Database::open()
{
	if(m_database.open())
		return true;
	else
	{
		QString errorText = m_database.lastError().text();
		raiseError(errorText);
		return false;
	}
}

bool Database::exec(QSqlQuery& query)
{
	if (query.exec()) return true;
	else
	{
		QString errorText = query.lastError().text();
		raiseError(errorText);
		return false;
	}
}

void Database::raiseError(const QString& errorText)
{
	emit PreferenceHelper::getHelper()->trigger(FloatingNote::Error, 20000, errorText);
}