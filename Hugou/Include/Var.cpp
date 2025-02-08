#include "Var.h"

Var* Var::m_var = nullptr;
QMutex Var::m_mutex;

Var::Var()
{
    calculateScale();
}

Var* Var::getVar()
{
    if (m_var == nullptr) {
        QMutexLocker locker(&m_mutex);
        if (m_var == nullptr) {
            m_var = new Var();
        }
    }
    return m_var;
}

void Var::calculateScale()
{
    qreal screenWidth = GetSystemMetrics(SM_CXSCREEN);
    m_scale = screenWidth / 1920;
    qputenv("QT_SCALE_FACTOR", QString::number(m_scale).toLatin1());
}

qreal Var::getScale() { return m_scale; }