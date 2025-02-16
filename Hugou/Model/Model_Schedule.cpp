#include "Model_Schedule.h"

ScheduleModel::ScheduleModel()
{
	// 创建数据表
	createMemoDatabase();
	createAwardDatabase();
	createReferenceDatabase();
	createMemoAndAwardDatabase();
	createMemoAndReferenceDatabase();
	createMemoAndSubMemoDatabase();

	m_memoSettingModel = new MemoSettingModel();
}

ScheduleModel::~ScheduleModel()
{
	delete m_memoSettingModel;
}

void ScheduleModel::createMemoDatabase()
{
	QSqlQuery creatQuery;
	creatQuery.prepare(
		"CREATE TABLE IF NOT EXISTS memo("
		"ID                   INTEGER      NOT NULL PRIMARY KEY AUTOINCREMENT, "
		"Sketch               VARCHAR(255) NOT NULL, "
		"Template             VARCHAR(255) NOT NULL, "
		"Type                 TINYINT      NOT NULL, "
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
		"HasReference         BIT      DEFAULT 0"
		");"
	);
	Database::exec(creatQuery);
}

void ScheduleModel::createAwardDatabase()
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
	Database::exec(creatQuery);
}

void ScheduleModel::createReferenceDatabase()
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
	Database::exec(creatQuery);
}

void ScheduleModel::createMemoAndAwardDatabase()
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
	Database::exec(creatQuery);
}

void ScheduleModel::createMemoAndReferenceDatabase()
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
	Database::exec(creatQuery);
}

void ScheduleModel::createMemoAndSubMemoDatabase()
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
	Database::exec(creatQuery);
}

void ScheduleModel::addMemo(Memo& memo)
{
	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO memo(Sketch, Type, Template, Status, PostponeFlag, "
		"TimePeriod_F, TimePeriod_L, TimePoint, ImportanceAndUrgency,"
		"Detail, HasSubMemo, HasAward, HasReference)"
		"VALUES(:Sketch, :Type, :Template, :Status, :PostponeFlag, "
		":TimePeriod_F, :TimePeriod_L, :TimePoint, :Importance, :ImportanceDegree, "
		":Detail, :HasSubMemo, :HasAward, :HasReference);"
	);
	insertQuery.bindValue(":Sketch", memo.sketch);
	insertQuery.bindValue(":Type", QString::number(memo.memoType));
	insertQuery.bindValue(":Template", memo.memoTemplate.name);
	insertQuery.bindValue(":Status", QString::number(int(memo.status)));
	insertQuery.bindValue(":PostponeFlag", QString::number(int(memo.postponeFlag)));
	insertQuery.bindValue(":TimePeriod_F", memo.timePeriod_f);
	insertQuery.bindValue(":TimePeriod_L", memo.timePeriod_l);
	insertQuery.bindValue(":TimePoint", memo.timePoint);
	insertQuery.bindValue(":ImportanceAndUrgency", QString::number(int(memo.importanceAndUrgency)));
	insertQuery.bindValue(":Detail", memo.detail);
	insertQuery.bindValue(":HasSubMemo", QString::number(int(memo.hasSubMemo)));
	insertQuery.bindValue(":HasAward", QString::number(int(memo.hasAward)));
	insertQuery.bindValue(":HasReference", QString::number(int(memo.hasReference)));
	Database::exec(insertQuery);
	int lastID = insertQuery.lastInsertId().toInt();
	memo.ID = lastID;
	//insertQuery.prepare(
	//	"INSERT INTO task(Sketch, Type, Status, PostponeFlag, "
	//	"TimePeriod_F, TimePeriod_L, TimePoint, Importance, Detail, Award, "
	//	"PreTask, PostTask)"
	//	"VALUES(:Sketch, :Type, :Status, :PostponeFlag, "
	//	":TimePeriod_F, :TimePeriod_L, :TimePoint, :Importance, :Detail, :Award, "
	//	":PreTask, :PostTask);"
	//);
	//insertQuery.bindValue(":Sketch", task.sketch);
	//insertQuery.bindValue(":Type", QString::number(task.taskType));
	//insertQuery.bindValue(":Status", QString::number(int(task.status)));
	//insertQuery.bindValue(":PostponeFlag", QString::number(int(task.postponeFlag)));
	//insertQuery.bindValue(":TimePeriod_F", task.timePeriod_f);
	//insertQuery.bindValue(":TimePeriod_L", task.timePeriod_l);
	//insertQuery.bindValue(":TimePoint", task.timePoint);
	//insertQuery.bindValue(":Importance", QString::number(int(task.importance)));
	//insertQuery.bindValue(":Detail", task.detail);
	//insertQuery.bindValue(":Award", task.award);
	//insertQuery.bindValue(":PreTask", QString::number(task.preTask));
	//insertQuery.bindValue(":PostTask", QString::number(task.postTask));
	//Database::exec(insertQuery);
	//int lastID = insertQuery.lastInsertId().toInt();
	//task.ID = lastID;
}

void ScheduleModel::addMemoAndAwardRelation(int memoID, int awardID)
{
	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO memo_award(MemoID, AwardID)"
		"VALUES(:MemoID, :AwardID);"
	);
	insertQuery.bindValue(":MemoID", memoID);
	insertQuery.bindValue(":AwardID", awardID);
	Database::exec(insertQuery);
}

void ScheduleModel::addMemoAndReferenceRelation(int memoID, int referenceID)
{
	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO memo_reference(MemoID, ReferenceID)"
		"VALUES(:MemoID, :ReferenceID);"
	);
	insertQuery.bindValue(":MemoID", memoID);
	insertQuery.bindValue(":ReferenceID", referenceID);
	Database::exec(insertQuery);
}

void ScheduleModel::addMemoAndSubMemoRelation(int memoID, int subMemoID)
{
	QSqlQuery insertQuery;
	insertQuery.prepare(
		"INSERT INTO memo_reference(MemoID, SubMemoID)"
		"VALUES(:MemoID, :SubMemoID);"
	);
	insertQuery.bindValue(":MemoID", memoID);
	insertQuery.bindValue(":SubMemoID", subMemoID);
	Database::exec(insertQuery);
}

void ScheduleModel::readMemoDatabase()
{
	QSqlQuery selectQuery;
	selectQuery.prepare(
		"SELECT ID, Sketch, Type, Status, PostponeFlag, "
		"TimePeriod_F, TimePeriod_L, TimePoint, ImportanceAndUrgency, Detail, RetentionPeriod, "
		"HasSubMemo, HasAward, HasReference FROM memo"
	);
	Database::exec(selectQuery);
	if (selectQuery.next())
	{
		while (selectQuery.next()) {
			Memo memo = Memo();
			memo.ID = selectQuery.value(0).toInt();
			memo.sketch = selectQuery.value(1).toString();
			memo.memoType = selectQuery.value(2).toInt();
			memo.status = selectQuery.value(3).toInt();
			memo.postponeFlag = selectQuery.value(4).toBool();
			memo.timePeriod_f = selectQuery.value(5).toDateTime();
			memo.timePeriod_l = selectQuery.value(6).toDateTime();
			memo.timePoint = selectQuery.value(7).toDateTime();
			memo.importanceAndUrgency = static_cast<MemoImportanceAndUrgency>(selectQuery.value(8).toInt());
			memo.detail = selectQuery.value(9).toString();
			memo.retentionPeriod = selectQuery.value(10).toInt();
			memo.hasSubMemo = selectQuery.value(11).toBool();
			memo.hasAward = selectQuery.value(12).toBool();
			memo.hasReference = selectQuery.value(13).toBool();
			QSqlQuery query;
			// 子备忘录
			if (memo.hasSubMemo)
			{
				query.prepare(
					"SELECT SubMemoID FROM memo_submemo WHERE MemoID = " + QString::number(memo.ID)
				);
				if (query.next())
					while (query.next())
						memo.subMemo.append(query.value(0).toInt());
				query.clear();
			}
			// 奖励
			if (memo.hasAward)
			{
				query.prepare(
					"SELECT awardID FROM memo_award WHERE MemoID = " + QString::number(memo.ID)
				);
				if (query.next())
					while (query.next())
						memo.award.append(query.value(0).toInt());
				query.clear();
			}
			// 参考资源
			if (memo.hasReference)
			{
				query.prepare(
					"SELECT referenceID FROM memo_award WHERE MemoID = " + QString::number(memo.ID)
				);
				if (query.next())
					while (query.next())
						memo.reference.append(query.value(0).toInt());
				query.clear();
			}
			m_memoList.append(memo);
		}
	}
}

void ScheduleModel::deleteMemoRequest(int ID)
{
	QString recycleBin;
	preferenceHelper::getHelper()->getpreferenceValue("recycleBin", recycleBin);
	if (recycleBin == "on")
	{
		QString retentionPeriod;
		preferenceHelper::getHelper()->getpreferenceValue("retentionPeriod", retentionPeriod);
		updateMemo(ID, "retentionPeriod", retentionPeriod);
	}
	else deleteMemo(ID);
}

void ScheduleModel::deleteMemo(int ID)
{
	QSqlQuery deleteQuery;
	deleteQuery.prepare(
		"DELETE * FROM task WHERE ID = :ID;"
	);
	deleteQuery.bindValue(":ID", QString::number(ID));
	Database::exec(deleteQuery);
}

void ScheduleModel::updateMemo(int ID, QString propertyName, QString value)
{
	QSqlQuery updateQuery;
	updateQuery.prepare(
		"UPDATE task SET :propertyName = :value WHERE ID = :ID;"
	);
	updateQuery.bindValue(":propertyName", propertyName);
	updateQuery.bindValue(":value", value);
	updateQuery.bindValue(":ID", QString::number(ID));
	Database::exec(updateQuery);
}