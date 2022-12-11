#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QStyledItemDelegate>
#include <QToolTip>
namespace XES
{
	class MyListViewItemDelegate : public QStyledItemDelegate
	{
		Q_OBJECT
	public:
		MyListViewItemDelegate(QWidget* parent = nullptr);
		~MyListViewItemDelegate();

		void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const;

		bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index);
	private:
		QWidget* mpParent;
	};

}


#endif // MYLISTVIEW_H
