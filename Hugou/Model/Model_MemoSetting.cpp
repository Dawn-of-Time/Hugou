#include "Model_MemoSetting.h"

MemoSettingModel::MemoSettingModel()
{
	readMemoTypeLabelData();
	readMemoTypeData();
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
			MemoTypeLabel memoTypeLabel;
			memoTypeLabel.ID = selectQuery.value(0).toInt();
			memoTypeLabel.name = selectQuery.value(1).toString();
			m_labelMap.insert(memoTypeLabel.ID, MemoTypeLabel{ memoTypeLabel.ID, memoTypeLabel.name });
			m_typeLabelList.append(memoTypeLabel);
			m_typeLabelMap.insert(memoTypeLabel.ID, QList<MemoType>());
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
			MemoType memoType;
			memoType.ID = selectQuery.value(0).toInt();
			memoType.name = selectQuery.value(1).toString();
			memoType.color = QColor(selectQuery.value(2).toString());
			memoType.label = m_labelMap[selectQuery.value(3).toInt()];
			memoType.priority = selectQuery.value(4).toInt();
			if (memoType.priority) m_priorityTypeList.append(memoType);
			m_typeList.append(memoType);
			m_typeLabelMap[memoType.label.ID].append(memoType);
		}
	}
	std::sort(m_priorityTypeList.begin(), m_priorityTypeList.end(), [](const MemoType& m1, const MemoType& m2) {
		return std::tie(m1.priority) < std::tie(m2.priority);
		});
}