#ifndef EV_HBWIDGET_H
#define EV_HBWIDGET_H

#include <QWidget>
#include "mycombobox.h"
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include "DataStruct.h"

class EV_HBWidget : public QWidget
{
	Q_OBJECT

public:
	EV_HBWidget(QWidget* parent, EV_DATA_TYPE d);
	~EV_HBWidget();

	void init();

	void setKey(const QString&);
	void setValue(QVariant&);
	bool setRange(QString&);

	QString getKey()const;
	QVariant getValue()const;
	EV_DATA_TYPE getType() const;
	QString getRange()const;
	//是否数据已被修改
	bool isAlter()const;

	void resizeEvent(QResizeEvent* e);

private:
	void setOldVariant(QVariant& v);
private:
	EV_DATA_TYPE mDataType;
	QHBoxLayout* layout;
	QLabel* l;
	QWidget* w;

	QVariant oldV;
};


#endif // EV_HBWIDGET_H
