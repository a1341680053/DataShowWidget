#include "MyListViewItemDelegate.h"

#include <QPainter>
#include <QMouseEvent>
#include <QStringListModel>

using namespace XES;


MyListViewItemDelegate::MyListViewItemDelegate(QWidget* parent)
	:mpParent(parent)
{

}

MyListViewItemDelegate::~MyListViewItemDelegate()
{

}

void MyListViewItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QRect rect = option.rect;

	QString txt = index.data(Qt::EditRole).toString();

	/*QStyleOptionViewItem viewoption(option);
	initStyleOption(&viewoption,index);
	if (option.state.testFlag(QStyle::State_HasFocus))
	{
		viewoption.state = viewoption.state^QStyle::State_HasFocus;
	}*/

	painter->setPen(QPen(QColor(Qt::black)));
	//画按钮
	{
		painter->drawLine(rect.right() - 10, rect.top() + (rect.height() - 10) / 2, rect.right(), rect.bottom() - (rect.height() - 10) / 2);
		painter->drawLine(rect.right(), rect.top() + (rect.height() - 10) / 2, rect.right() - 10, rect.bottom() - (rect.height() - 10) / 2);
	}

	//画txt
	{
		painter->save();

		QFont font;
		font.setPixelSize(12);
		painter->setFont(font);
		QRect txtRect(rect.left(), rect.top(), rect.width() - 20, rect.height());
		QFontMetrics met(font);
		txt = met.elidedText(txt, Qt::ElideRight, rect.width() - 20);
		painter->drawText(txtRect, txt);

		painter->restore();
	}
}

bool MyListViewItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index)
{
	QRect rect = option.rect;
	if (mpParent)
	{
		rect = mpParent->rect();
	}
	QRect del(rect.right() - 10, rect.top() + (rect.height() - 10) / 2, 10, 10);


	QMouseEvent* mevent = static_cast<QMouseEvent*>(event);
	if (event->type() == QEvent::MouseMove)
	{
		QToolTip::showText(QCursor::pos(), index.data().toString());
	}

	if (event->type() == QEvent::MouseButtonPress)
	{
		if (del.contains(mevent->pos()))
		{
			QStringListModel* mymodel = dynamic_cast<QStringListModel*>(model);
			mymodel->removeRow(index.row());
		}
		else
		{

		}
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
