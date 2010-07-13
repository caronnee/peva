#include "controlpanel.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	controlPanel w;
	w.show();
	return a.exec();
}
