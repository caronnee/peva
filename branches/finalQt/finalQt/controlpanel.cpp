#include "controlpanel.h"
#include <iostream>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>

controlPanel::controlPanel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	this->insWin = new QMainWindow(this);
	ins.setupUi(this->insWin);

	//this->insWin->show();
	//QObject::connect(this->ui.mapButton, SIGNAL(clicked()), &b, SLOT(close()));
//	new QPushButton("ddd",this->insWin);
//	new QPushButton("ddd2",this->insWin);
	QScrollArea * scr = new QScrollArea;
	myCentral = new QWidget;
	scr->setWidget(myCentral);
	this->insWin->setCentralWidget( scr );

	QVBoxLayout * l = new QVBoxLayout;
	l->addWidget(new QLabel("ttt"));
	l->addWidget(new QLabel("ttt2"));
	l->addWidget(new QLabel("ttt3"));

	myCentral->setLayout(l);
	QObject::connect(this->ui.InstrructionButton, SIGNAL(clicked()), this->insWin, SLOT(show()));
	QObject::connect(this->ui.mapButton, SIGNAL(clicked()), this, SLOT(mySet()));
}

void controlPanel::mySet()
{
	//zistit, ci sa layout netreba nahodou deinizializovat
	std::cout << "test";

	QHBoxLayout * l = new QHBoxLayout;
	l->addWidget(new QLabel("ttt"));
	l->addWidget(new QLabel("ttt2"));
	l->addWidget(new QLabel("ttt3"));
	myCentral->layout()->addItem(l);
	new QPushButton("d",this->insWin);
	myCentral->layout()->addWidget(new QPushButton("d1",this->myCentral));
	myCentral->setLayout(myCentral->layout());
	insWin->setCentralWidget(myCentral);
}
controlPanel::~controlPanel()
{

}
