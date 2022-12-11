#include "messagewidget.h"
#include <QDebug>
#include <QLineEdit>
#include "messagewidget.h"

using namespace std;
MessageWidget::MessageWidget(QWidget *parent)
	: QWidget(parent)
{

	this->setContextMenuPolicy(Qt::CustomContextMenu);

}

MessageWidget::~MessageWidget()
{
	
}

void MessageWidget::initMenu()
{
	connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_rightClicked(QPoint)));

	mpMenu = new QMenu(this);

	connect(mpMenu,SIGNAL(triggered(QAction*)),this,SLOT(slot_actionClicked(QAction*)));
	mpAddAction = new QAction("添加",this);
	mpaltAction = new QAction("修改",this);
	mpdelAction = new QAction("删除",this);

	
}

void MessageWidget::addRow(EV_DataType& data)
{
	shared_ptr<EV_HBWidget> hb= make_shared<EV_HBWidget>(this,data.dataT);
	hb->setKey(data.dataK);
	hb->setRange(data.dataRange);
	hb->setValue(data.dataV);
	hb->setMaximumHeight(25);
	hb->setMinimumHeight(21);
	hb->setMaximumWidth(this->width()-10);
	hb->setMinimumWidth(this->width()-10);
	if (mHBMap.find(data.dataK) == mHBMap.end())
	{
		mHBMap.insert(data.dataK,hb);

		hb->setGeometry(5,5 + 30*mHBMap.size()-1,hb->width(),hb->height());
	}
}

QMap<QString,EV_DataType> MessageWidget::getDataList() const
{
	auto ite = mHBMap.begin();

	QMap<QString,EV_DataType> ret;
	for (ite;ite != mHBMap.end();++ite)
	{
		QString key=ite.key();
		EV_DataType temp;
		temp.dataK = key;
		temp.dataT = ite->get()->getType();
		if (temp.dataT == EV_INT || temp.dataT == EV_DOUBLE)
		{
			temp.dataRange = ite->get()->getRange();
		}
		temp.dataV = ite->get()->getValue();
		if (ret.find(key) == ret.end())
		{
			ret.insert(key,temp);
		}
	}
	return ret;
}

QMap<QString,EV_DataType> MessageWidget::getAlterDataList() const
{
	auto ite = mHBMap.begin();

	QMap<QString,EV_DataType> ret;
	for (ite;ite != mHBMap.end();++ite)
	{
		
		QString key=ite.key();
		bool ree= ite->get()->isAlter();
		if (!ite->get()->isAlter() || ret.find(key) != ret.end())
		{
			continue;
		}
		EV_DataType temp;
		temp.dataK = key;
		temp.dataT = ite->get()->getType();
		if (temp.dataT == EV_INT || temp.dataT == EV_DOUBLE)
		{
			temp.dataRange = ite->get()->getRange();
		}
		temp.dataV = ite->get()->getValue();
		ret.insert(key,temp);
	}
	return ret;
}

void MessageWidget::resizeEvent(QResizeEvent *e)
{
	auto ite = mHBMap.begin();

	for (ite;ite != mHBMap.end();++ite)
	{
		auto temp = ite.value();
		temp->setMaximumWidth(this->width()-10);
		temp->setMinimumWidth(this->width()-10);
	}
}

bool MessageWidget::contains(const QString& str) const
{

	if (mHBMap.find(str) != mHBMap.end())
	{
		return true;
	}
	return false;
}

QString MessageWidget::findPos(const QPoint& pos) const
{
	QMap<QString,std::shared_ptr<EV_HBWidget>>::const_iterator ite=mHBMap.begin();

	for (;ite != mHBMap.end();++ite)
	{
		QRect rect=ite->get()->rect();
		if (rect.contains(pos))
		{
			return ite.key();
		}

	}
	return QString();
}

void MessageWidget::slot_rightClicked(QPoint pos)
{

}

void MessageWidget::slot_actionClicked(QAction* action)
{

}
