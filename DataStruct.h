#ifndef _DATASTRUCT_H_
#define _DATASTRUCT_H_
#include <QVariant>

enum EV_DATA_TYPE
{
	EV_INT,
	EV_DOUBLE,
	EV_QSTRING,
	EV_COMBOX,
	EV_BOOL
};

struct EV_DataType
{
	EV_DATA_TYPE dataT;
	QString dataK;
	QString dataRange;//范围
	QVariant dataV;
};

#endif
