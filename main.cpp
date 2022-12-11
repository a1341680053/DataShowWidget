#include "datashowwidget.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	DataShowWidget w;
	w.show();
	return a.exec();
}
