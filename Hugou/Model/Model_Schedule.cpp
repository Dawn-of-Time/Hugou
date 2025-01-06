#include "Model_Schedule.h"

ScheduleModel::ScheduleModel()
{
	m_database = new Database();
	m_database->open();
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS task_db("
		"ID              INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Sketch          VARCHAR(255) NOT NULL, "
		"Type            TINYINT      NOT NULL, "
		"Status          TINYINT      NOT NULL, "
		"PostponeFlag    BIT      DEFAULT 0, "
		"TimePeriod_F    DATETIME DEFAULT NULL, "
		"TimePeriod_L    DATETIME DEFAULT NULL, "
		"TimePoint       DATETIME DEFAULT NULL, "
		"Importance      TINYINT  DEFAULT 0, "
		"Detail          TEXT     DEFAULT NULL, "
		"Award           TEXT     DEFAULT NULL, "
		"PreTask         INTEGER  DEFAULT -1, "
		"PostTask        INTEGER  DEFAULT -1, "
		"RetentionPeriod TINYINT  DEFAULT -1"
		");"
	);
	m_database->exec(creatQuery);
}

ScheduleModel::~ScheduleModel()
{
	delete m_database;
}
void ScheduleModel::addTask(Task& task)
{
	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO task_db(Sketch, Type, Status, PostponeFlag, "
		"TimePeriod_F, TimePeriod_L, TimePoint, Importance, Detail, Award, "
		"PreTask, PostTask)"
		"VALUES(:Sketch, :Type, :Status, :PostponeFlag, "
		":TimePeriod_F, :TimePeriod_L, :TimePoint, :Importance, :Detail, :Award, "
		":PreTask, :PostTask);"
	);
	insertQuery.bindValue(":Sketch", task.sketch);
	insertQuery.bindValue(":Type", QString::number(task.taskType));
	insertQuery.bindValue(":Status", QString::number(int(task.status)));
	insertQuery.bindValue(":PostponeFlag", QString::number(int(task.postponeFlag)));
	insertQuery.bindValue(":TimePeriod_F", task.timePeriod_f);
	insertQuery.bindValue(":TimePeriod_L", task.timePeriod_l);
	insertQuery.bindValue(":TimePoint", task.timePoint);
	insertQuery.bindValue(":Importance", QString::number(int(task.importance)));
	insertQuery.bindValue(":Detail", task.detail);
	insertQuery.bindValue(":Award", task.award);
	insertQuery.bindValue(":PreTask", QString::number(task.preTask));
	insertQuery.bindValue(":PostTask", QString::number(task.postTask));
	m_database->exec(insertQuery);
	int lastID = insertQuery.lastInsertId().toInt();
	task.ID = lastID;
}

void ScheduleModel::deleteTaskRequest(int ID)
{
	QString recycleBin;
	SettingsHelper::getHelper()->getSettingsValue("recycleBin", recycleBin);
	if (recycleBin == "on")
	{
		QString retentionPeriod;
		SettingsHelper::getHelper()->getSettingsValue("retentionPeriod", retentionPeriod);
		updateTask(ID, "retentionPeriod", retentionPeriod);
	}
	else deleteTask(ID);
}

void ScheduleModel::deleteTask(int ID)
{
	QSqlQuery deleteQuery;
	deleteQuery.prepare(
		"DELETE * FROM task_db WHERE ID = :ID;"
	);
	deleteQuery.bindValue(":ID", QString::number(ID));
	m_database->exec(deleteQuery);
}

void ScheduleModel::updateTask(int ID, QString propertyName, QString value)
{
	QSqlQuery updateQuery;
	updateQuery.prepare(
		"UPDATE task_db SET :propertyName = :value WHERE ID = :ID;"
	);
	updateQuery.bindValue(":propertyName", propertyName);
	updateQuery.bindValue(":value", value);
	updateQuery.bindValue(":ID", QString::number(ID));
	m_database->exec(updateQuery);
}