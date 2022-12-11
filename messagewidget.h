#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include "DataStruct.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include "ev_hbwidget.h"
#include <memory>

class MessageWidget : public QWidget
{
	Q_OBJECT

public:
	MessageWidget(QWidget* parent);
	~MessageWidget();

	//初始化右键菜单
	void initMenu();

	void addRow(EV_DataType& data);
	//获取此页面所有数据
	QMap<QString, EV_DataType> getDataList()const;
	//获取此页面已修改数据
	QMap<QString, EV_DataType> getAlterDataList()const;

	void resizeEvent(QResizeEvent* e);
	//检查键是否存在
	bool contains(const QString& str)const;

	QString findPos(const QPoint& pos)const;
public slots:
	//右键点击
	void slot_rightClicked(QPoint);
	//按钮点击
	void slot_actionClicked(QAction* action);


private:
	QMap<QString, std::shared_ptr<EV_HBWidget>> mHBMap;

	QMenu* mpMenu;

	QAction* mpAddAction;
	QAction* mpdelAction;
	QAction* mpaltAction;
};

#endif // MESSAGEWIDGET_H
