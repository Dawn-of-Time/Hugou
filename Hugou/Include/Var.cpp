#include "Var.h"
#include <QDebug>

Var::Var()
{
    calculateScale();
}


Var* Var::getVar()
{
    static Var var;
    return &var;
}

void Var::calculateScale()
{
    qreal screenWidth = GetSystemMetrics(SM_CXSCREEN);
    m_scale = screenWidth / 1920 * 0.9;
    qputenv("QT_SCALE_FACTOR", QString::number(m_scale).toLatin1());
}

qreal Var::getScale() { return m_scale; }