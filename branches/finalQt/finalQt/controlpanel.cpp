#include "controlpanel.h"
#include <iostream>
#include <QHBoxLayout>
#include <QLabel>

controlPanel::controlPanel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	this->insWin = new QMainWindow(this);
	ins.setupUi(this->insWin);

	QWidget * myCentral = new QWidget(this->insWin);
	QVBoxLayout * vLayout = new QVBoxLayout(myCentral);
	QScrollArea * scrollArea = new QScrollArea(myCentral);
	vLayout->addWidget(scrollArea);      
       
      //set up parameters for scroll area
	scrollArea->setWidgetResizable(false);      
       
      //create another widget with a QVBoxLayout
	QVBoxLayout * scrollAreaVLayout = new QVBoxLayout();
	scrollAreaWidgetContents = new QWidget(); 
	scrollAreaWidgetContents->setLayout(scrollAreaVLayout);
	scrollAreaVLayout->setSizeConstraint(QLayout::SetFixedSize);  
       
      //add scrolling widget to scroller
	scrollArea->setWidget(scrollAreaWidgetContents);      
	this->insWin->setCentralWidget(myCentral);

	QObject::connect(this->ui.mapButton, SIGNAL(clicked()), this, SLOT(mySet()));
	insWin->show();
}

void controlPanel::mySet()
{
	scrollAreaWidgetContents->layout()->addWidget(new QPushButton("test", scrollAreaWidgetContents));
}
controlPanel::~controlPanel() { }
