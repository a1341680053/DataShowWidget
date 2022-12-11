#include "ev_hbwidget.h"
using namespace XES;
EV_HBWidget::EV_HBWidget(QWidget* parent, EV_DATA_TYPE d)
	: QWidget(parent), mDataType(d)
{
	init();
}

EV_HBWidget::~EV_HBWidget()
{
	if (layout)
	{
		delete layout;
	}
	if (l)
	{
		delete l;
	}

	if (w)
	{
		switch (mDataType)
		{
		case EV_INT:
			delete dynamic_cast<QSpinBox*>(w);
			break;
		case EV_DOUBLE:
			delete dynamic_cast<QDoubleSpinBox*>(w);
			break;
		case EV_BOOL:
			delete dynamic_cast<QDoubleSpinBox*>(w);
			break;
		case EV_QSTRING:
			delete dynamic_cast<QLineEdit*>(w);
			break;
		case EV_COMBOX:
			delete dynamic_cast<MyComboBox*>(w);
			break;
		}
	}

}

void EV_HBWidget::init()
{
	layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	l = new QLabel(this);
	w = nullptr;
	switch (mDataType)
	{
	case EV_INT:
		w = new QSpinBox(this);
		break;
	case EV_DOUBLE:
		w = new QDoubleSpinBox(this);
		break;
	case EV_BOOL:
	{
		QComboBox* com = new QComboBox(this);
		com->addItems(QStringList() << "False" << "True");
		com->setCurrentIndex(0);
		w = com;
	}
	break;
	case EV_QSTRING:
		w = new QLineEdit(this);
		break;
	case EV_COMBOX:
		w = new MyComboBox(this);
		break;
	}
	w->setFixedWidth(80);
	layout->addWidget(l);
	layout->addWidget(w);
	this->setLayout(layout);
}

void EV_HBWidget::setKey(const QString& str)
{
	l->setText(str);
}

QString EV_HBWidget::getKey() const
{
	return l->text();
}

void EV_HBWidget::setValue(QVariant& data)
{
	setOldVariant(data);
	switch (mDataType)
	{
	case EV_INT:
		dynamic_cast<QSpinBox*>(w)->setValue(data.toInt());
		break;
	case EV_DOUBLE:
		dynamic_cast<QDoubleSpinBox*>(w)->setValue(data.toDouble());
		break;
	case EV_BOOL:
		dynamic_cast<QComboBox*>(w)->setCurrentIndex(data.toBool());
		break;
	case EV_QSTRING:
		dynamic_cast<QLineEdit*>(w)->setText(data.toString());
		break;
	case EV_COMBOX:
	{
		MyComboBox* w1 = dynamic_cast<MyComboBox*>(w);
		QString str = data.toString();
		QStringList strL = str.split("_");
		if (strL.size() != 2)
		{
			return;
		}
		int currIndex = strL[0].toInt();
		strL = strL[1].split(",");
		w1->clear();
		w1->insertItems(0, strL);
		w1->setCurrentIndex(currIndex);
	}
	break;
	}

}

bool EV_HBWidget::setRange(QString& data)
{
	QStringList strList = data.split("-");
	if (strList.count() != 2)
	{
		return false;
	}
	switch (mDataType)
	{
	case EV_INT:
	{
		int min = strList[0].toInt();
		int max = strList[1].toInt();
		dynamic_cast<QSpinBox*>(w)->setMinimum(min);
		dynamic_cast<QSpinBox*>(w)->setMaximum(max);
	}
	return true;
	case EV_DOUBLE:
	{
		double min = strList[0].toDouble();
		double max = strList[1].toDouble();
		dynamic_cast<QDoubleSpinBox*>(w)->setMaximum(min);
		dynamic_cast<QDoubleSpinBox*>(w)->setMaximum(max);
	}
	return true;
	case EV_BOOL:
	case EV_QSTRING:
	case EV_COMBOX:
	default:
		return false;
	}
}

QVariant EV_HBWidget::getValue() const
{
	QVariant v1;
	switch (mDataType)
	{
	case EV_INT:
		v1 = dynamic_cast<QSpinBox*>(w)->value();
		break;
	case EV_DOUBLE:
		v1 = dynamic_cast<QDoubleSpinBox*>(w)->value();
		break;
	case EV_BOOL:
		v1 = (bool)(dynamic_cast<QComboBox*>(w)->currentIndex());
		break;
	case EV_QSTRING:
		v1 = dynamic_cast<QLineEdit*>(w)->text();
		break;
	case EV_COMBOX:
	{
		MyComboBox* w1 = dynamic_cast<MyComboBox*>(w);
		int boxCount = w1->count();
		QString ret = QString("%1_").arg(w1->currentIndex());

		for (int i = 0; i < boxCount; ++i)
		{
			ret += w1->itemText(i);
			if (i + 1 != boxCount)
			{
				ret += ",";
			}
		}
		v1 = ret;
	}
	break;
	}
	return v1;
}

EV_DATA_TYPE EV_HBWidget::getType() const
{
	return mDataType;
}

QString EV_HBWidget::getRange() const
{
	QString ret;
	switch (mDataType)
	{
	case EV_INT:
	{
		int min = dynamic_cast<QSpinBox*>(w)->minimum();
		int max = dynamic_cast<QSpinBox*>(w)->maximum();

		ret = QString("%1-%2").arg(min).arg(max);
	}
	break;
	case EV_DOUBLE:
	{
		double min = min = dynamic_cast<QDoubleSpinBox*>(w)->minimum();
		double max = max = dynamic_cast<QDoubleSpinBox*>(w)->maximum();

		ret = QString("%1-%2").arg(min).arg(max);
	}
	break;
	case EV_BOOL:
	case EV_QSTRING:
	case EV_COMBOX:
	default:
		return nullptr;
	}
	return ret;
}

bool EV_HBWidget::isAlter() const
{
	QVariant v1 = getValue();

	return v1 != oldV;
}

void EV_HBWidget::resizeEvent(QResizeEvent* e)
{
	int hiii = this->height();
	l->setFixedHeight(this->height() - 3);
	w->setFixedHeight(this->height() - 3);
}

void EV_HBWidget::setOldVariant(QVariant& v)
{
	oldV = v;
}
