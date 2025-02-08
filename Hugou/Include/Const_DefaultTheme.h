#pragma once

#include <QString>

// 默认主题
const QString defaultGeneralStyleSheet =
QString("HugouView#hugou { background-color: #F0F4FD; }")
+ QString("QWidget#asideBarAndStackedWidget { background-color: transparent; }")
+ QString("QStackedWidget#stackedWidget { margin-bottom: 10px; margin-right: 10px; border-radius: 10px; background-color: rgba(255, 255, 255, 0.8);}");

const QString defaultAsideBarStyleSheet = 
QString("QLabel { padding-left: 6px; color:#666666; background-color: transparent; }")
+ QString("QLabel#userAvatar { padding: 0px; border-radius: 24px; border: none; color: balck; background-color: transparent;} ")
+ QString("QLabel#userNickname { border: none; color: balck; background-color: transparent;} ")
+ QString("QLabel#userID { border: none; color: balck; background-color: transparent;} ")
+ QString("QPushButton[status=\"default\"] { border-radius: 10px; }")
+ QString("QPushButton[status=\"default\"] > QLabel { padding: 0px; margin :0px; color: #434343; background-color: transparent; }")
+ QString("QPushButton[status=\"current\"] { border-radius: 10px;}")
+ QString("QPushButton[status=\"current\"] > QLabel { padding: 0px; margin :0px; color: #377FED; background-color: transparent; }");

const QString defaultpreferenceStyleSheet =
QString("QStackedWidget { background-color: transparent; border: none }")
+ QString("QTreeWidget { background-color: transparent; border: none }")
+ QString("QListWidget { background-color: transparent; border: none; outline: none; margin-left: 20px; margin-right: 12px; margin-top: 2px; margin-bottom: 2px }")
+ QString("QListWidget::item:hover { background-color: transparent }")
+ QString("QPushButton { border: none }")
+ QString("QComboBox { border: none; border-radius: 5px; padding: 3px; background-color: #A2CBEE; }")
+ QString("QComboBox:hover { background-color: #5591DC; }")
+ QString("QComboBox QAbstractItemView { outline: none; margin-top: 5px; border-radius: 5px; background-color: #A2CBEE; }")
+ QString("QComboBox QAbstractItemView::item:hover { padding: 3px; color: black; border-radius: 5px; background-color: #5591DC; }")
+ QString("QComboBox QAbstractItemView::item:selected { padding: 3px; color: white; border-radius: 5px; background-color: #5591DC; }")
+ QString("QComboBox::down-arrow { image: url(\":/icon/down_bla.png\"); width: 20px; }")
+ QString("QComboBox::drop-down { border: none; }");
