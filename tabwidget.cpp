#include "tabwidget.h"
#include <QDebug>
using namespace std;
TabWidget::TabWidget(QWidget* parent)
	: QTabWidget(parent)
{

}

TabWidget::~TabWidget()
{
	mWidgetMap.clear();
	mQScrollMap.clear();
}

void TabWidget::loadTab(QMap<int, QString> tabM)
{
	for (auto ite = tabM.begin(); ite != tabM.end(); ++ite)
	{
		shared_ptr<MessageWidget> ptr = make_shared<MessageWidget>(this);
		if (mWidgetMap.find(ite.key()) == mWidgetMap.end())
		{
			mWidgetMap.insert(ite.key(), ptr);
		}
		this->addTab(ptr.get(), ite.value());
	}
}

void TabWidget::addItem_EV(int index, EV_DataType& data)
{
	auto temp = mWidgetMap[index];
	temp->addRow(data);
}

QMap<QString, EV_DataType> TabWidget::getDataList(int index) const
{
	auto temp = mWidgetMap[index];
	return temp->getDataList();
}

QMap<QString, EV_DataType> TabWidget::getAlterDataList(int index) const
{
	auto temp = mWidgetMap[index];
	return temp->getAlterDataList();
}
