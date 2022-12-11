#include "mycombobox.h"
using namespace XES;
XES::MyComboBox::MyComboBox(QWidget* parent)
	:QComboBox(parent),
	mpStringListModel(new QStringListModel(parent))
{

	mpItemDelegate = new MyListViewItemDelegate((QWidget*)this->view());

	this->setModel(mpStringListModel);
	this->setItemDelegate(mpItemDelegate);
	this->setEditable(true);
}

XES::MyComboBox::MyComboBox(const QStringList& strList, QWidget* parent /*= nullptr*/)
	:QComboBox(parent),
	mpItemDelegate(new MyListViewItemDelegate),
	mpStringListModel(new QStringListModel(this))
{
	this->setModel(mpStringListModel);
	this->setItemDelegate(mpItemDelegate);
	mpStringListModel->setStringList(strList);
}

XES::MyComboBox::~MyComboBox()
{
	delete mpItemDelegate;
	delete mpStringListModel;
}
