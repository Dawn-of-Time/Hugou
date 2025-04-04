#include "Model/Include/Model_MemoSetting.h"

MemoSettingModel::MemoSettingModel(QObject* parent)
	:QObject(parent)
{
	readMemoTypeLabelData();
	readMemoTypeData();

	MemoTemplate* defaultTemplate = new MemoTemplate
	{
		"Default",
		QColor("#377FED"),
		{ Type, Time, ImportanceAndUrgency, Detail, SubMemo, Award, Reference }
	};
	m_templateList.append(defaultTemplate);
}

MemoSettingModel::~MemoSettingModel()
{
	qDeleteAll(m_templateList);
	m_templateList.clear();
	qDeleteAll(m_labelMap);
	m_labelMap.clear();
	for (QMap<int, QList<MemoType*>>::iterator it = m_typeLabelMap.begin(); it != m_typeLabelMap.end(); it++)
	{
		qDeleteAll(it.value());
		it.value().clear();
	}
	m_typeLabelMap.clear();
	m_typeLabelList.clear();
	m_typeList.clear();
}

void MemoSettingModel::readMemoTypeLabelData()
{
	QSqlQuery selectQuery;
	selectQuery.prepare(
		"SELECT ID, Name FROM memotype_label"
	);
	if (Database::exec(selectQuery))
	{
		while (selectQuery.next()) {
			MemoTypeLabel* memoTypeLabel = new MemoTypeLabel;
			memoTypeLabel->ID = selectQuery.value(0).toInt();
			memoTypeLabel->name = selectQuery.value(1).toString();
			m_labelMap.insert(memoTypeLabel->ID, memoTypeLabel);
			m_typeLabelList.append(memoTypeLabel);
			m_typeLabelMap.insert(memoTypeLabel->ID, QList<MemoType*>());
		}
	}
}

void MemoSettingModel::readMemoTypeData()
{
	QSqlQuery selectQuery;
	selectQuery.prepare(
		"SELECT ID, Name, Color, Label, Priority FROM memotype"
	);
	if (Database::exec(selectQuery))
	{
		while (selectQuery.next()) {
			MemoType* memoType = new MemoType;
			memoType->ID = selectQuery.value(0).toInt();
			memoType->name = selectQuery.value(1).toString();
			memoType->color = QColor(selectQuery.value(2).toString());
			memoType->label = *m_labelMap[selectQuery.value(3).toInt()];
			memoType->priority = selectQuery.value(4).toInt();
			m_typeList.append(memoType);
			m_typeLabelMap[memoType->label.ID].append(memoType);
		}
	}
}