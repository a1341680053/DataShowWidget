#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include "MyListViewItemDelegate.h"
#include <QStringListModel>

namespace XES
{
	class MyComboBox : public QComboBox
	{
		Q_OBJECT

	public:
		MyComboBox(QWidget* parent = nullptr);
		MyComboBox(const QStringList& strList, QWidget* parent = nullptr);
		~MyComboBox();

	private:
		MyListViewItemDelegate* mpItemDelegate;
		QStringListModel* mpStringListModel;
	};
}


#endif // MYCOMBOBOX_H
