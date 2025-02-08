#pragma once
#include <Windows.h>
#include <QString>
#include <QMutexLocker>

class Var
{
public:
	static Var* getVar(); 
	qreal getScale();

private:
	static Var* m_var;
	static QMutex m_mutex;
	qreal m_scale;
	Var();
	void calculateScale();
};
