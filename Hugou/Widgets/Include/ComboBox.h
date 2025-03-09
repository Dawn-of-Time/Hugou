#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>

class ComboBox :
    public QPushButton
{
public:
	ComboBox(QWidget* parent);
	
	inline int currentIndex() { return m_currentIndex; };
	inline QString currentText() { return m_currentText; };

	//void setCurrentIndex(int index);
	//void setCurrentText(QString text);

private:
	int m_currentIndex = 0;
	QString m_currentText = "";

	QLabel* m_dropDownLabel;
	QListWidget* m_listWidget;
	void setupUi();
	//void addItem(QString item);
};

