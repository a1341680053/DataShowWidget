#pragma once

#include <QtWidgets/QWidget>
#include "ui_datashowwidget.h"

#include <QSystemTrayIcon>
#include "adddatawidget.h"

class TabWidget;
class DataShowWidget : public QWidget
{
	Q_OBJECT

public:
	DataShowWidget(QWidget* parent = nullptr);
	~DataShowWidget();
	void init();
	void initMenu();
	void testLoad();

	void hideEvent(QHideEvent*);

	void showEvent(QShowEvent*);
public slots:
	void slot_rightClicked(QPoint);
	//菜单按钮点击槽
	void slot_actionClicked(QAction* action);
	//切换tab窗口
	void slot_switchoverTab(int);
private:
	Ui::DataShowWidgetClass ui;

	QMenu* mpMenu;
	QAction* mpDelAction;

	QListWidgetItem* pitchOnItem;

	//最小化托盘
	QSystemTrayIcon* mpTrayIcon;
	QMenu* mpSysMenu;
	QAction* mpShowAction;
};
