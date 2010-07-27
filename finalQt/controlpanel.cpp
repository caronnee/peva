#include "controlpanel.h"
#include <iostream>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QDir>

controlPanel::controlPanel(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	this->insWin = new QMainWindow(this);
	this->mapWin = new QDialog(this);

	ins.setupUi(this->insWin);
	dialog.setupUi(this->mapWin);

	this->mapWin->show();
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
	QObject::connect(this->dialog.fromChosen, SIGNAL(clicked()), this, SLOT(unchoose()));
	QObject::connect(this->dialog.toChosen, SIGNAL(clicked()), this, SLOT(choose()));
	QObject::connect(this->dialog.listPossibilities, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(changeDir(QListWidgetItem *)));

	QFileDialog * d = new QFileDialog(this->mapWin);
	directory.setPath(".");
	QListWidgetItem * setDir = new QListWidgetItem(".");
	changeDir(setDir);
	delete setDir;
	//insWin->show();
}

void controlPanel::unchoose()
{
	QList<QListWidgetItem *> itm = this->dialog.listView->selectedItems();
	for (int i =0; i< itm.size(); i++)
		delete this->dialog.listView->takeItem(this->dialog.listView->row(itm[i]));
}
void controlPanel::changeDir(QListWidgetItem *itm)
{
	if (!QFileInfo(directory.absoluteFilePath(itm->text())).isDir())
		return;
	//do not go higher than maps
	directory.setPath(directory.absoluteFilePath(itm->text()));
		//remove all
	while( this->dialog.listPossibilities->count()!=0)
		delete this->dialog.listPossibilities->takeItem(0);
	QDir ths(".");
	if (ths.canonicalPath() != directory.canonicalPath())
		this->dialog.listPossibilities->addItem("..");
	QStringList l = directory.entryList(QStringList("*"),
		QDir::Files | QDir::NoSymLinks | QDir::Dirs |QDir::NoDotAndDotDot);
	for (int i =0; i< l.size(); i++)
		this->dialog.listPossibilities->addItem(l[i]);
}
void controlPanel::choose()
{
	QList<QListWidgetItem *> itm = this->dialog.listPossibilities->selectedItems();
	for (int i =0; i< itm.size(); i++)
	{
		if (!QFileInfo(directory.absoluteFilePath(itm[i]->text())).isFile()) //if it is file, add
			continue;
		this->dialog.listView->addItem((itm[i])->text());
	}
	this->dialog.listView->clearSelection();
}
void controlPanel::mySet()
{
	scrollAreaWidgetContents->layout()->addWidget(new QPushButton("test", scrollAreaWidgetContents));
	this->insWin->show();
}
controlPanel::~controlPanel() { }
