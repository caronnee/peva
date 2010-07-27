#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <vector>
#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include "ui_controlpanel.h"
#include <QScrollArea>
#include "ui_instructions.h"
#include "ui_maps.h"
#include <list>
#include <QFile>
#include <QDir>

class controlPanel : public QMainWindow
{
	Q_OBJECT

public slots:;
	void mySet();
	void choose();
	void unchoose();
	void changeDir(QListWidgetItem *itm);

public:
	controlPanel(QWidget *parent = 0, Qt::WFlags flags = 0);
	~controlPanel();

private:
	QWidget * myCentral;
	QWidget * scrollAreaWidgetContents;
	QMainWindow * insWin;
	Ui::controlPanelClass ui;
	QDialog * mapWin;
	Ui::Instruction ins;

	Ui::Dialog dialog;
	QDir directory;
};

#endif // CONTROLPANEL_H
