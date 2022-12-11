#include "datashowwidget.h"
#include <QMenu>
#include <QAction>
#include "tabwidget.h"

using namespace std;
const QString c_strDel = QString::fromLocal8Bit("删除");

DataShowWidget::DataShowWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
}

DataShowWidget::~DataShowWidget()
{
}

void DataShowWidget::init()
{
	initMenu();
	testLoad();
	pitchOnItem = nullptr;
	connect(ui.listWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slot_rightClicked(QPoint)));
	connect(mpMenu, SIGNAL(triggered(QAction*)), this, SLOT(slot_actionClicked(QAction*)));
	connect(ui.listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(slot_switchoverTab(int)));

	mpTrayIcon = new QSystemTrayIcon;
	mpSysMenu = new QMenu(this);
	mpShowAction = new QAction("显示", this);
	mpSysMenu->addAction(mpShowAction);
	mpTrayIcon->setContextMenu(mpSysMenu);

	mpTrayIcon->setIcon(QIcon("D:\\9.ico"));

	connect(mpSysMenu, SIGNAL(triggered(QAction*)), this, SLOT(slot_actionClicked(QAction*)));




}

void DataShowWidget::initMenu()
{
	mpMenu = new QMenu(this);

	mpDelAction = new QAction(c_strDel, mpMenu);

	mpMenu->addAction(mpDelAction);
}

void DataShowWidget::testLoad()
{
	ui.listWidget->addItem("test1");
	ui.listWidget->addItem("test2");
	ui.listWidget->addItem("test3");

	auto tabW = new TabWidget(ui.stackedWidget);
	ui.stackedWidget->insertWidget(0, tabW);
	auto tabW1 = new TabWidget(ui.stackedWidget);
	ui.stackedWidget->insertWidget(1, tabW1);
	auto tabW2 = new TabWidget(ui.stackedWidget);
	ui.stackedWidget->insertWidget(2, tabW2);

	QMap<int, QString> strMap;
	strMap.insert(0, "测试1");
	strMap.insert(1, "测试2");
	strMap.insert(2, "测试3");
	strMap.insert(3, "测试4");

	tabW->loadTab(strMap);
	tabW1->loadTab(strMap);
	tabW2->loadTab(strMap);



	EV_DataType ev1;
	ev1.dataT = EV_INT;
	ev1.dataK = "测试key1";
	ev1.dataV = 12;

	EV_DataType ev2;
	ev2.dataT = EV_DOUBLE;
	ev2.dataK = "测试key2";
	ev2.dataV = 12.25;
	EV_DataType ev3;
	ev3.dataT = EV_COMBOX;
	ev3.dataK = "测试key3";
	ev3.dataV = "2_1,2,3,45,6";

	tabW->addItem_EV(0, ev1);
	tabW->addItem_EV(0, ev2);
	tabW->addItem_EV(0, ev3);
	ui.stackedWidget->setCurrentIndex(0);

}

void DataShowWidget::hideEvent(QHideEvent*)
{
	setWindowFlags(Qt::Tool);
	mpTrayIcon->show();
}

void DataShowWidget::showEvent(QShowEvent*)
{
	mpTrayIcon->hide();

}

void DataShowWidget::slot_rightClicked(QPoint pos)
{
	pitchOnItem = ui.listWidget->itemAt(pos);
	mpMenu->exec(QCursor::pos());
}

void DataShowWidget::slot_actionClicked(QAction* action)
{
	if (mpShowAction == action)
	{
		setWindowFlags(Qt::Widget);
		this->show();
		return;
	}


	QString name = action->text();
	if (name == c_strDel)
	{
		if (!pitchOnItem)
		{
			return;
		}
		int num = ui.listWidget->row(pitchOnItem);
		ui.listWidget->takeItem(num);
		pitchOnItem = nullptr;
		QWidget* w = ui.stackedWidget->widget(num);
		ui.stackedWidget->removeWidget(w);
		if (w)
		{
			TabWidget* tw = dynamic_cast<TabWidget*>(w);

			auto kt = tw->getAlterDataList(0);
			if (tw)
			{
				delete tw;
			}
		}
	}
}

void DataShowWidget::slot_switchoverTab(int number)
{
	TabWidget* w = dynamic_cast<TabWidget*>(ui.stackedWidget->currentWidget());
	int index = w->currentIndex();
	ui.stackedWidget->setCurrentIndex(number);
	w = dynamic_cast<TabWidget*>(ui.stackedWidget->currentWidget());
	w->setCurrentIndex(index);

	AddDataWidget* W_ = new AddDataWidget;


	W_->exec();

	if (W_->isOk())
	{
		EV_DataType d1 = W_->getData();
	}
	delete W_;
}