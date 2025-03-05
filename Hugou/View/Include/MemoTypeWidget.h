#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Include/Struct_Memo.h"

class MemoTypeWidget :
    public QPushButton
{
public:
    MemoTypeWidget(MemoType& memoType, QWidget* parent);
    void updateUi(const MemoType& newType);
    MemoType& getMemo() { return m_memoType; }

private:
    MemoType& m_memoType;
    QVBoxLayout* m_layout;
    QLabel* m_icon;
    QLabel* m_type;
    void setupUi();
};

