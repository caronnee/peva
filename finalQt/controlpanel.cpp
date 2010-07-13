#include "controlpanel.h"
#include <QHBoxLayout>
#include <QLabel>

controlPanel::controlPanel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	this->insWin = new QMainWindow(this);
	ins.setupUi(this->insWin);

	//this->insWin->show();
	//QObject::connect(this->ui.mapButton, SIGNAL(clicked()), &b, SLOT(close()));
	QObject::connect(this->ui.InstrructionButton, SIGNAL(clicked()), this->insWin, SLOT(show()));
	QObject::connect(this->ui.mapButton, SIGNAL(clicked()), this, SLOT(mySet()));
}

void controlPanel::mySet()
{
	//zistit, ci sa layout netreba nahodou deinizializovat
	QHBoxLayout * l = new QHBoxLayout(this->insWin);
	l->addWidget(new QLabel("ttt"));
	l->addWidget(new QLabel("ttt2"));
	l->addWidget(new QLabel("ttt3"));
    insWin->show();
}
controlPanel::~controlPanel()
{

}