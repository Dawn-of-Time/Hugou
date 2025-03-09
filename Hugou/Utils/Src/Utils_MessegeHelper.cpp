#include "Utils/Include/Utils_MessegeHelper.h"

MessegeHelper::MessegeHelper()
    : QObject()
{
    connect(this, &MessegeHelper::trigger, this, &MessegeHelper::deal);
}

MessegeHelper* MessegeHelper::getHelper()
{
	static MessegeHelper helper;
	return &helper;
}

void MessegeHelper::setMode(const MessegeHelperMode& mode)
{
    m_mode = mode;
    if (mode == MessegeHelperMode::UIPreparedMode)
        for (const QPair<FloatingNote::NoteType, QPair<QString, QString>>& note : m_noteList)
            FloatingNoteManager::getManager()->raiseFloatingNote(note.first, note.second.first, note.second.second);
}

void MessegeHelper::deal(FloatingNote::NoteType type, int code, const QString& otherInfo)
{
    QString content = "";
    QString subcontent = "";
    switch (type)
    {
    case FloatingNote::Success:
    {
        content = successCodeMap.value(code, { "" });
        subcontent = otherInfo;
        break;
    }
    case FloatingNote::Information:
        break;
    case FloatingNote::Dialog:
        break;
    case FloatingNote::Warning:
        break;
    case FloatingNote::Error:
    {
        QStringList list = errorCodeMap.value(code, { "Unknown error code.",  "No solution found." });
        content = list[0] + "(Error Code: " + QString::number(code) + ")";
        subcontent = list[1] + otherInfo;
        break;
    }
    default:
        break;
    }
    if (m_mode == MessegeHelperMode::UIPreparedMode) FloatingNoteManager::getManager()->raiseFloatingNote(type, content, subcontent);
    else m_noteList.append(qMakePair(type, qMakePair(content, subcontent)));
}