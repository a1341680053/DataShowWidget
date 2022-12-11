#include "adddatawidget.h"
#include <QMessageBox>
AddDataWidget::AddDataWidget(QWidget* parent)
	: QDialog(parent),
	mbOk(false)
{
	this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);

	init();
}

AddDataWidget::~AddDataWidget()
{
	delete mpKey;
	delete mpValue;
	delete mpType_;
	delete mpKey_In;
	delete mpType_Select;

	clearValueW();
}

bool AddDataWidget::isOk() const
{
	return mbOk;
}

EV_DataType AddDataWidget::getData()
{
	EV_DataType ret;
	ret.dataK = mpKey_In->text();
	ret.dataT = (EV_DATA_TYPE)mpType_Select->currentIndex();
	if (mpValue_Range)
	{
		QString range_ = mpValue_Range->text();
		QStringList rangeList = range_.split("-");
		ret.dataRange = mpValue_Range->text();
	}
	switch (ret.dataT)
	{
	case EV_INT:
		if (mpValue_Int)
		{
			ret.dataV = mpValue_Int->value();
		}
		break;
	case EV_DOUBLE:
		if (mpValue_Double)
		{
			ret.dataV = mpValue_Double->value();
		}
		break;
	case EV_BOOL:
		if (mpValue_Bool)
		{
			ret.dataV = (bool)mpValue_Bool->currentIndex();
		}
		break;
	case EV_QSTRING:
		if (mpValue_Str)
		{
			ret.dataV = mpValue_Str->text();
		}
		break;
	case EV_COMBOX:
		if (mpValue_Combo)
		{
			QString data;
			for (int i = 0; i < mpValue_Combo->count(); ++i)
			{
				data += mpValue_Combo->itemText(i);
				if (i + 1 < mpValue_Combo->count())
				{
					data += ",";
				}
			}
			ret.dataV = QString("%1_%2").arg(mpValue_Combo->currentIndex())
				.arg(data);
		}
		break;
	default:
		break;
	}
	return ret;
}

void AddDataWidget::init()
{
	this->setFixedSize(180, 175);

	mpKey = new QLabel(this);
	mpKey->setText("数据名称:");
	mpKey->setGeometry(5, 5, 65, 25);

	mpKey_In = new QLineEdit(this);
	mpKey_In->setGeometry(75, 8, 100, 19);

	mpType_ = new QLabel(this);
	mpType_->setText("数据类型:");
	mpType_->setGeometry(5, 35, 65, 25);

	mpType_Select = new QComboBox(this);
	QStringList strList = QStringList() << "整数" << "浮点数" << "字符串" << "下拉框数据" << "布尔值";
	mpType_Select->addItems(strList);
	mpType_Select->setGeometry(75, 35, 100, 25);

	mpValue = new QLabel(this);
	mpValue->setText("数据值: ");
	mpValue->setGeometry(5, 70, 65, 25);

	mpOk = new QPushButton(this);
	mpOk->setText("确认");
	mpOk->setGeometry(5, 140, 50, 25);
	mpOk->setFocusPolicy(Qt::NoFocus);

	mpCancel = new QPushButton(this);
	mpCancel->setText("取消");
	mpCancel->setGeometry(this->width() - 55, 140, 50, 25);
	mpCancel->setFocusPolicy(Qt::NoFocus);

	mpValue_Bool = nullptr;
	mpValue_Combo = nullptr;
	mpValue_Double = nullptr;
	mpValue_Int = nullptr;
	mpValue_Range = nullptr;
	mpValue_Str = nullptr;
	mpRange = nullptr;
	mpValidator = nullptr;





	setIntType();

	connect(mpType_Select, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_currentIndexChanged(int)));
	connect(mpOk, SIGNAL(clicked()), this, SLOT(slot_OkClicked()));
	connect(mpCancel, SIGNAL(clicked()), this, SLOT(slot_CancelClicked()));
}

void AddDataWidget::clearValueW()
{
	if (mpValue_Bool)
	{
		delete mpValue_Bool;
		mpValue_Bool = nullptr;
	}
	if (mpValidator)
	{
		delete mpValidator;
		mpValidator = nullptr;
	}
	if (mpValue_Combo)
	{
		delete mpValue_Combo;
		mpValue_Combo = nullptr;
	}
	if (mpValue_Double)
	{
		delete mpValue_Double;
		mpValue_Double = nullptr;
	}
	if (mpValue_Range)
	{
		delete mpValue_Range;
		mpValue_Range = nullptr;
	}
	if (mpValue_Str)
	{
		delete mpValue_Str;
		mpValue_Str = nullptr;
	}
	if (mpValue_Int)
	{
		delete mpValue_Int;
		mpValue_Int = nullptr;
	}
	if (mpRange)
	{
		delete mpRange;
		mpRange = nullptr;
	}

}

void AddDataWidget::setIntType()
{
	clearValueW();

	mpValue_Int = new QSpinBox(this);
	mpValue_Int->setGeometry(75, 70, 100, 25);
	mpValue_Int->show();

	mpRange = new QLabel(this);
	mpRange->setText("数值范围:");
	mpRange->setGeometry(5, 105, 65, 25);
	mpRange->show();

	mpValue_Range = new QLineEdit(this);
	mpValue_Range->setGeometry(75, 105, 100, 25);
	mpValue_Range->setPlaceholderText("例：0-999");
	QRegExp rx("^[0-9]*-[0-9]*$");
	mpValidator = new QRegExpValidator(rx, mpValue_Range);
	mpValue_Range->setValidator(mpValidator);
	connect(mpValue_Range, SIGNAL(editingFinished()), this, SLOT(slot_Range()));
	mpValue_Range->show();
}

void AddDataWidget::setDoubleType()
{
	clearValueW();

	mpValue_Double = new QDoubleSpinBox(this);
	mpValue_Double->setGeometry(75, 70, 100, 25);
	mpValue_Double->show();

	mpRange = new QLabel(this);
	mpRange->setText("数值范围:");
	mpRange->setGeometry(5, 105, 65, 25);
	mpRange->show();

	mpValue_Range = new QLineEdit(this);
	mpValue_Range->setGeometry(75, 105, 100, 25);
	mpValue_Range->setPlaceholderText("例：0-1");
	QRegExp rx("^[0-9]+(.[0-9]*)?-[0-9]+(.[0-9]*)?$");

	mpValidator = new QRegExpValidator(rx, mpValue_Range);
	mpValue_Range->setValidator(mpValidator);
	mpValue_Range->show();
}

void AddDataWidget::setBoolType()
{
	clearValueW();

	mpValue_Bool = new QComboBox(this);
	mpValue_Bool->setGeometry(75, 70, 100, 25);
	mpValue_Bool->addItem("是");
	mpValue_Bool->addItem("否");
	mpValue_Bool->show();
}

void AddDataWidget::setStrType()
{
	clearValueW();

	mpValue_Str = new QLineEdit(this);
	mpValue_Str->setGeometry(75, 70, 100, 25);
	mpValue_Str->show();
}

void AddDataWidget::setComboBoxType()
{
	clearValueW();

	mpValue_Combo = new XES::MyComboBox(this);
	mpValue_Combo->setGeometry(75, 70, 100, 25);
	QRegExp rx("[^,\x22]+");
	mpValidator = new QRegExpValidator(rx, mpValue_Combo->lineEdit());
	mpValue_Combo->lineEdit()->setValidator(mpValidator);
	mpValue_Combo->lineEdit()->setPlaceholderText("回车添加");
	mpValue_Combo->show();
}

void AddDataWidget::slot_currentIndexChanged(int index)
{
	switch (index)
	{
	case EV_INT:
		setIntType();
		break;
	case EV_DOUBLE:
		setDoubleType();
		break;
	case EV_BOOL:
		setBoolType();
		break;
	case EV_QSTRING:
		setStrType();
		break;
	case EV_COMBOX:
		setComboBoxType();
		break;
	default:
		break;
	}
}

void AddDataWidget::slot_OkClicked()
{
	if (mpValue_Range)
	{
		QString range_ = mpValue_Range->text();
		QStringList rangeList = range_.split("-");
		if (rangeList.size() != 2)
		{
			QMessageBox::warning(nullptr, "错误", "数值范围格式错误", "确认");
			return;
		}
		else
		{
			double r1 = rangeList[0].toDouble();
			double r2 = rangeList[1].toDouble();

			if (r1 >= r2)
			{
				QMessageBox::warning(nullptr, "错误", "数值范围错误", "确认");
				return;
			}
		}
	}
	if (mpKey_In)
	{
		if (mpKey_In->text().isEmpty())
		{
			QMessageBox::warning(nullptr, "错误", "请输入数据名称", "确认");
			return;
		}

	}
	mbOk = true;
	this->close();
}

void AddDataWidget::slot_CancelClicked()
{
	mbOk = false;
	this->close();
}

void AddDataWidget::slot_Range()
{
	if (mpValue_Range)
	{
		QString range_ = mpValue_Range->text();
		QStringList rangeList = range_.split("-");
		if (rangeList.size() != 2)
		{
			QMessageBox::warning(nullptr, "错误", "数值范围格式错误", "确认");
			return;
		}
		else
		{
			double r1 = rangeList[0].toDouble();
			double r2 = rangeList[1].toDouble();

			if (r1 >= r2)
			{
				QMessageBox::warning(nullptr, "错误", "数值范围错误", "确认");
				return;
			}
			if (mpValue_Int)
			{
				mpValue_Int->setMinimum(r1);
				mpValue_Int->setMaximum(r2);
			}
			if (mpValue_Double)
			{
				mpValue_Double->setMinimum(r1);
				mpValue_Double->setMaximum(r2);
			}
		}
	}
}
