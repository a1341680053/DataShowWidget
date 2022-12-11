#ifndef ADDDATAWIDGET_H
#define ADDDATAWIDGET_H

#include <QDialog>
#include "mycombobox.h"
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include "DataStruct.h"
class AddDataWidget : public QDialog
{
	Q_OBJECT

public:
	AddDataWidget(QWidget* parent = nullptr);
	~AddDataWidget();
	bool isOk()const;
	EV_DataType getData();
private:
	void init();
	//清理数值Value窗口
	void clearValueW();
	//整形值状态
	void setIntType();
	//浮点数值状态
	void setDoubleType();
	//布尔值状态
	void setBoolType();
	//字符串状态
	void setStrType();
	//下拉框状态
	void setComboBoxType();

private slots:
	void slot_currentIndexChanged(int);
	//确认
	void slot_OkClicked();
	//取消
	void slot_CancelClicked();
	//设置数值范围
	void slot_Range();
private:
	QLabel* mpKey;//
	QLabel* mpValue;//
	QLabel* mpType_;

	QLineEdit* mpKey_In;//数据名输入
	QComboBox* mpType_Select;//数据种类选择

	QSpinBox* mpValue_Int;//int形数据
	QDoubleSpinBox* mpValue_Double;//double形数据
	QLineEdit* mpValue_Range;//数据范围
	QLabel* mpRange;
	QComboBox* mpValue_Bool;//布尔型数据
	QLineEdit* mpValue_Str;//字符串型数据
	XES::MyComboBox* mpValue_Combo;//下拉框类型数据

	QRegExpValidator* mpValidator;

	bool mbOk;
public:
	QPushButton* mpOk;
	QPushButton* mpCancel;
};

#endif // ADDDATAWIDGET_H
