#pragma once

#include <QStringList>
#include <map>

// 主题颜色： {theme-color, hover-selected-color}
const QStringList defaultThemeColor = QStringList(
	{ "#006699", "#008AB1" });
const QStringList springThemeColor = QStringList(
	{ "#00cc99", "#99ffcc" });
const QStringList summerThemeColor = QStringList(
	{ "#0099ff", "#66ccff" });
const QStringList autumnThemeColor = QStringList(
	{ "#ff6633", "#ffcc99" });
const QStringList winterThemeColor = QStringList(
	{ "#666666", "#d9d9d9" });

// 主题映射表
const std::map<QString, QStringList> themeMap = {
		{"Default", defaultThemeColor},
		{"Spring", springThemeColor},
		{"Summer", summerThemeColor},
		{"Autumn", autumnThemeColor},
		{"Winter", winterThemeColor} };