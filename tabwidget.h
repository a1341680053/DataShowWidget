#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QMap>
#include "messagewidget.h"
#include <QScrollArea>

class TabWidget : public QTabWidget
{
	Q_OBJECT

public:
	TabWidget(QWidget* parent);
	~TabWidget();
	void loadTab(QMap<int, QString> tabM);

	void addItem_EV(int index, EV_DataType& data);
	//获取index页面所有数据
	QMap<QString, EV_DataType> getDataList(int index)const;
	//获取index页面已修改数据
	QMap<QString, EV_DataType> getAlterDataList(int index)const;
private:
	QMap<int, std::shared_ptr<MessageWidget>> mWidgetMap;
	QMap<int, std::shared_ptr<QScrollArea>> mQScrollMap;
};

#endif // TABWIDGET_H
