#pragma once
#include <Windows.h>
#include <QString>

class Var
{
public:
	static Var* getVar(); 
	qreal getScale();

private:
	qreal m_scale;
	Var();
	void calculateScale();
};
